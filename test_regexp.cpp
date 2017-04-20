#include <iostream>
#include <memory>
// #include <regexp>
#include <string>

#include <boost/lexical_cast.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/regex.hpp>
#include <set>

using namespace std;

int main() {
  string exp = "ether://[64:80:99:41:54:00]";

  static const boost::regex protocolExp("(\\w+\\d?(\\+\\w+)?)://([^/]*)(\\/[^?]*)?");
  // pattern for IPv6 address enclosed in [ ], with optional port number
  static const boost::regex v6Exp("^\\[([a-fA-F0-9:]+)\\](?:\\:(\\d+))?$");
  // pattern for Ethernet address in standard hex-digits-and-colons notation
  static const boost::regex etherExp("^\\[((?:[a-fA-F0-9]{1,2}\\:){5}(?:[a-fA-F0-9]{1,2}))\\]$");
  // pattern for IPv4-mapped IPv6 address, with optional port number
  static const boost::regex v4MappedV6Exp("^\\[::ffff:(\\d+(?:\\.\\d+){3})\\](?:\\:(\\d+))?$");
  // pattern for IPv4/hostname/fd/ifname, with optional port number
  static const boost::regex v4HostExp("^([^:]+)(?:\\:(\\d+))?$");
  // String match
  boost::smatch protocolMatch;
  if (!boost::regex_match(exp, protocolMatch, protocolExp)) {
    return false;
  }

  std::string m_scheme;
  std::string m_host;
  std::string m_port;
  std::string m_path;

  m_scheme = protocolMatch[1];
  const std::string& authority = protocolMatch[3];
  m_path = protocolMatch[4];

  bool m_isV6;

  if (authority.empty()) {
    // UNIX, internal
  }
  else {
    boost::smatch match;
    m_isV6 = boost::regex_match(authority, match, v6Exp);
    if (m_isV6 ||
        boost::regex_match(authority, match, etherExp) ||
        boost::regex_match(authority, match, v4MappedV6Exp) ||
        boost::regex_match(authority, match, v4HostExp)) {
      m_host = match[1];
      m_port = match[2];
    }
    else {
      std::cout << "not v6" << std::endl;
    }
  }
  /**
   * match the regex in authority and put the results in match,
   * the regex is defined and pass to the third of boost::regex_match
   */
  boost::smatch match;
  if (m_isV6) {
    cout << "match v6" << endl;
  }
  if (boost::regex_match(authority, match, etherExp)) {
    cout << "match ether" << endl;
  }
  if (boost::regex_match(authority, match, v4MappedV6Exp)) {
    cout << "match v4 mapped v6" << endl;
  }
  if (boost::regex_match(authority, match, v4HostExp)) {
    cout << "match v4 host" << endl;
  }

  std::cout << "m_scheme: " << m_scheme << std::endl;
  std::cout << "authority: " << authority << std::endl;
  std::cout << "m_path: " << m_path << std::endl;
  std::cout << "m_host: " << m_host << std::endl;
  std::cout << "m_port: " << m_port << std::endl;

}
