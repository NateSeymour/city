#include "Assembly.h"

using namespace city;

Symbol Assembly::Lookup(std::string const &symbol)

{
    return this->symbol_table_[symbol];
}
