#pragma once

#include <memory>
#include <optional>
#include <stdexcept>
#include <string_view>
#include <vector>

#include <string_tracker.hpp>

#include "error.hpp"
#include "expression.hpp"

namespace conftaal {

using string_pool::string_tracker;

class ParseError : public Error {
public:
	using Error::Error;
};

class Matcher;

extern Matcher match_end_of_file;

class Parser {

public:
	explicit Parser(string_tracker & tracker, std::string_view source)
		: string_tracker_(tracker), source_(source) {}

	std::unique_ptr<Expression> parse_expression(Matcher const & end = match_end_of_file);
	std::unique_ptr<ListExpression> parse_list(Matcher const & end = match_end_of_file);
	std::unique_ptr<ObjectExpression> parse_object(Matcher const & end = match_end_of_file);

	static bool is_identifier_start(char c);
	static std::string_view parse_identifier(std::string_view & source);
	static std::unique_ptr<IdentifierExpression> parse_identifier_expression(std::string_view & source);

private:
	std::unique_ptr<Expression> parse_expression_atom(Matcher const & end);
	bool parse_more_expression(std::unique_ptr<Expression> & expr, Matcher const & end);

	std::unique_ptr<StringLiteralExpression> parse_string_literal();
	std::unique_ptr<Expression> parse_number();

	std::optional<std::string_view> parse_end(Matcher const &, bool consume = true);

private:
	string_tracker & string_tracker_;
	std::string_view source_;

};

}
