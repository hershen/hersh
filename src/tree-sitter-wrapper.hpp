#include <tree_sitter/api.h>

#include <iostream>

namespace hersh {
extern "C" {
    TSLanguage *tree_sitter_bash();
}

class TreeSitterTree {
 public:
  explicit TreeSitterTree(TSTree* tree) :
    tree_(tree) {}
  ~TreeSitterTree() {
    ts_tree_delete(tree_);
  }

 private:
  TSTree* tree_;

};

class TreeSitter {
 public:
  TreeSitter() {

    parser_ = ts_parser_new();

    ts_parser_set_language(parser_, tree_sitter_bash());


    /* TSNode root_node = ts_tree_root_node(tree); */

    /* std::string string = ts_node_string(root_node); */
    /* std::cout << string << std::endl; */
  }
  ~TreeSitter() {
    ts_parser_delete(parser_);
  }

  TreeSitterTree parse(const std::string& string) const {
    return TreeSitterTree(ts_parser_parse_string(
                          parser_,
                          NULL,
                          string.c_str(),
                          string.size()
                        )
        );

  }
 private:
  TSParser* parser_;
};
}
