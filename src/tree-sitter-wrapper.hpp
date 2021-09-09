#include <tree_sitter/api.h>

#include <iostream>

/* namespace hersh { */
extern "C" {
    TSLanguage *tree_sitter_bash();
}

class TreeSitter {
 public:
  TreeSitter() {
    std::cout << "In tree sitter" << std::endl;
    TSLanguage *tree_sitter_bash();

    TSParser *parser = ts_parser_new();

    ts_parser_set_language(parser, tree_sitter_bash());

    std::string sourceCode = "ls -la";

    TSTree *tree = ts_parser_parse_string(
      parser,
      NULL,
      sourceCode.c_str(),
      sourceCode.size()
    );

    TSNode root_node = ts_tree_root_node(tree);

    std::string string = ts_node_string(root_node);
    std::cout << string << std::endl;
  }
};
