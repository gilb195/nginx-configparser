#include "gtest/gtest.h"
#include "config_parser.h"

TEST(NginxConfigParserTest, SimpleConfig) {
  NginxConfigParser parser;
  NginxConfig out_config;

  bool success = parser.Parse("example_config", &out_config);

  EXPECT_TRUE(success);
}

TEST(NginxConfigTest, ToString) {
	NginxConfigStatement statement;
	statement.tokens_.push_back("foo");
	statement.tokens_.push_back("bar");
	EXPECT_EQ(statement.ToString(0), "foo bar;\n");
}

TEST(NginxConfigParserTest, ExtraEndBraceConfig) {
  NginxConfigParser parser;
  NginxConfig out_config;

  std::stringstream config_stream("server { listen   80; server_name foo.com; root /home/ubuntu/sites/foo/; }}");

  bool success = parser.Parse(&config_stream, &out_config);

  EXPECT_FALSE(success);
}

TEST(NginxConfigParserTest, MultipleBlockConfig) {
  NginxConfigParser parser;
  NginxConfig out_config;

  std::stringstream config_stream("server { listen   80; server_name foo.com; client { listen 10; } root /home/ubuntu/sites/foo/; }");

  bool success = parser.Parse(&config_stream, &out_config);

  EXPECT_TRUE(success);
}

// The following test fails with the given config_parser.cc code. The bug has been fixed and the test now passes.
TEST(NginxConfigParserTest, MissingEndBraceConfig) {
  NginxConfigParser parser;
  NginxConfig out_config;

  std::stringstream config_stream("server { listen   80; server_name foo.com; root /home/ubuntu/sites/foo/; ");

  bool success = parser.Parse(&config_stream, &out_config);

  EXPECT_FALSE(success);
}