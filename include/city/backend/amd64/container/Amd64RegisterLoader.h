#ifndef AMD64REGISTERLOADER_H
#define AMD64REGISTERLOADER_H

namespace city
{
    struct Amd64Translator;
    class Amd64Register;
    class ConstantDataContainer;

    struct Amd64RegisterLoader
    {
        Amd64Translator &translator;

        void Load(Amd64Register &target, ConstantDataContainer *container);
        void Load(Amd64Register &target, Amd64Register *container);
    };
} // namespace city

#endif // AMD64REGISTERLOADER_H
