#include "city/backend/NativeModule.h"

using namespace city;

NativeModule::NativeModule(std::string name, std::vector<std::uint8_t> data) : name_(std::move(name)), data_(std::move(data)) {}
