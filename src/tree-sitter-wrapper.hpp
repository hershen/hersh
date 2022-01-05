extern "C" {
  #include <tree_sitter/api.h>
}

#include <cassert>
#include <exception>
#include <fcntl.h>
#include <iostream>
#include <unistd.h>

namespace tree_sitter {
extern "C" {
    TSLanguage *tree_sitter_bash();
}

class parsingError : public std::exception
{

public:
  explicit parsingError(const std::string& message) :
    message_(message) {}

	const char * what () const throw () {
    return message_.c_str();
  }

private:
  std::string message_;
};

class Tree {
public:
  explicit Tree(TSTree* tree) :
    tree_(tree) {}

  ~Tree() {
    ts_tree_delete(tree_);
  }

  Tree(const Tree& other) :
    tree_(ts_tree_copy(other.tree_))
  {}

  Tree& operator=(const Tree& other)
  {
    if (this == &other) return *this;
    ts_tree_delete(tree_);
    tree_ = ts_tree_copy(other.tree_);
    return *this;
  }

  std::string stringify() const {
    TSNode root_node = ts_tree_root_node(tree_);

    std::cout << ts_node_type(root_node) << std::endl;
    std::cout << "named: " << ts_node_is_named(root_node) << std::endl;
    std::cout << "Number of children: " << ts_node_child_count(root_node) << std::endl;
    std::cout << "Number of named children: " << ts_node_named_child_count(root_node) << std::endl;

    /* TSNode ts_node_next_named_sibling(TSNode); */
    /* TSNode ts_node_prev_named_sibling(TSNode); */

    const auto c_str = ts_node_string(root_node);
    std::string string = c_str;
    free(c_str);
    return string;
  }

private:
  TSTree* tree_;
};

class Parser {
 public:
  Parser() {
    parser_ = ts_parser_new();

    const bool success = ts_parser_set_language(parser_, tree_sitter_bash());
    assert(success && "Could not set the parser language correctly. There was a version mismatch.");

    ts_parser_set_timeout_micros(parser_, 1'000'000'000);
    file_descriptor_ = open("GfgTest.dot", O_WRONLY , O_CREAT | O_TRUNC | O_SYNC);
    ts_parser_print_dot_graphs(parser_, file_descriptor_);

  }

  ~Parser() {
    ts_parser_delete(parser_);
    close(file_descriptor_);
  }

  Parser(const Parser& other) :
    parser_(other.parser_)
  {}

  Parser& operator=(const Parser& other)
  {
    if (this == &other) return *this;
    ts_parser_delete(parser_);
    parser_ = other.parser_;
    return *this;
  }

  Tree parse(const std::string& string) const {
    const auto parsed = ts_parser_parse_string(
                          parser_,
                          NULL,
                          string.c_str(),
                          string.size()
                          );

    if(!parsed) {
      throw parsingError("Failed to parse string: " + string); 
    }

    return Tree(parsed);
  }

  // Print a list of bash language symbols to cout
  void printSymbols() const {
    std::cout << "Bash has " << ts_language_symbol_count(tree_sitter_bash()) << " node types" << std::endl;
    for (int i=0; i< ts_language_symbol_count(tree_sitter_bash()); ++i) {
      std::cout << "Symbol " << i << ": " << ts_language_symbol_name(tree_sitter_bash(), i) << "\n";
    }
  }

  // Print a list of bash language fields to cout
  void printFields() const {
    std::cout << "Bash has " << ts_language_field_count(tree_sitter_bash()) << " field names" << std::endl;
    for (int i=1; i< ts_language_field_count(tree_sitter_bash());  ++i) {
      std::cout << "Field " << i << ": " << ts_language_field_name_for_id(tree_sitter_bash(), i) << "\n";
    }
  }

 private:
  int file_descriptor_;
  TSParser* parser_;
};
}
