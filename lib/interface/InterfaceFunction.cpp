#include <city/interface/InterfaceFunction.h>

using namespace city;

city::InterfaceFunction::InterfaceFunction(std::string name, city::Type return_type, std::vector<Type> arg_types, void *address) :
    Function(std::move(name), return_type, std::move(arg_types)), address_(address)
{
}
