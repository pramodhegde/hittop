// Return the result of the second grammar unless the first grammar successfully
// parses the input.
//
#ifndef HITTOP_PARSER_UNLESS_H
#define HITTOP_PARSER_UNLESS_H

#include "hittop/parser/parser.h"

namespace hittop {
namespace parser {

template <typename RejectGrammar, typename DefaultGrammar> struct Unless {};

template <typename RejectGrammar, typename DefaultGrammar>
class Parser<Unless<RejectGrammar, DefaultGrammar>> {
public:
  template <typename Range>
  auto operator()(const Range &input) const
      -> Fallible<decltype(std::begin(input))> {
    auto reject_result = Parse<RejectGrammar>(input);
    if (reject_result.error() == ParseError::INCOMPLETE) {
      return reject_result;
    }
    if (!reject_result.error()) {
      return {reject_result.consume(), ParseError::FAILED_CONDITION};
    }
    return Parse<DefaultGrammar>(input);
  }
};

} // namespace parser
} // namespace hittop

#endif // HITTOP_PARSER_UNLESS_H
