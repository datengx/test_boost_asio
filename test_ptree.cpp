/**
 *  Author: Da Teng
 *  Illustrate how boost property tree is used,
 *  possibly in big project
 *
 */


#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/info_parser.hpp>
#include <memory>
#include <iostream>
#include <string>
#include <fstream>
#include <utility>

using boost::property_tree::ptree;

class PtreeParser {
public:
  class Error : public std::runtime_error
  {
  public:
    explicit
    Error(const std::string& what)
      : std::runtime_error(what)
    {
    }
  };

  PtreeParser(const std::string& filename);

  PtreeParser(std::istream& input);

  void
  parse(std::istream& input);

  /** Parse with the full name of the node
   *
   */
  static bool
  parseYesNo(const boost::property_tree::ptree::value_type& option) {
    return parseYesNo(option.second, option.first);
    //return false;
  }

  static bool
  parseYesNo(const boost::property_tree::ptree& node, const std::string& key);

private:
  boost::property_tree::ptree m_tree;
};

PtreeParser::PtreeParser(const std::string& filename) {
  std::ifstream inputFile(filename);
  if (!inputFile.good() || !inputFile.is_open()) {
    BOOST_THROW_EXCEPTION(Error("Failed to read configuration file: " + filename));
  }
  parse(inputFile);
}

PtreeParser::PtreeParser(std::istream& input) {
  parse(input);
}

void
PtreeParser::parse(std::istream& input) {
  // Parse the tree and store the tree in m_tree
  boost::property_tree::read_info(input, m_tree);
}

bool
PtreeParser::parseYesNo(const boost::property_tree::ptree& node, const std::string& key) {

}


int main()
{
  std::string filename = "/home/da/dev/C++/test_modules/test.conf";
  std::unique_ptr<PtreeParser> tree_parser(new PtreeParser(filename));

  // tree_parser.get()->parse();


  // Outputing properties in the tree
  ptree pt;
  pt.put("C:.Windows.System", "20 files");

  boost::optional<std::string> c = pt.get_optional<std::string>("C:");
  std::cout << std::boolalpha << c.is_initialized() << '\n';

  pt.put_child("D:.Program Files", ptree{"50 files"}); // Insert a tree WITH a value "50 files"
  pt.add_child("D:.Program Files", ptree{"60 files"}); // Insert a tree WITH a value "60 files"
  //pt.put("D:.Program Files", "50 files");

  ptree d = pt.get_child("D:");
  //std::cout << d.get_value<std::string>() << std::endl; // this will be empty since D: does not have a value yet

  // iterate over the sub-directory
  for (const std::pair<std::string, ptree> &p : d)
    std::cout << p.second.get_value<std::string>() << '\n';

  boost::optional<ptree&> d_op = pt.get_child_optional("D:");
  std::cout << d_op.is_initialized() << '\n';
  for (const ptree::value_type& p : *d_op) {
    std::cout << p.first << '\n';
  }



  // std::cout << system.get_value<std::string>() << '\n';
}
