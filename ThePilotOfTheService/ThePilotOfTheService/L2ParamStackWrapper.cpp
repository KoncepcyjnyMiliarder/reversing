#include "L2ParamStackWrapper.hpp"
#include "PEStuff.hpp"

L2ParamStackWrapper::L2ParamStackStatic L2ParamStackWrapper::staticInstance;

L2ParamStackWrapper::L2ParamStackStatic::L2ParamStackStatic()
{
    L2StackConstructor = (void(__fastcall*)(L2ParamStack & stack, void* dummy, size_t initialDwordsNum))Utils::FindExport(Utils::LdrGetModuleHandle(L"Core.dll"), "??0L2ParamStack@@QAE@H@Z");
    L2StackPushBackV = (void(__fastcall*)(L2ParamStack & stack, void* dummy, void* val))Utils::FindExport(Utils::LdrGetModuleHandle(L"Core.dll"), "?PushBack@L2ParamStack@@QAEHPAX@Z");
    if (!L2StackPushBackV) L2StackPushBackV = (void(__fastcall*)(L2ParamStack & stack, void* dummy, void* val))Utils::FindExport(Utils::LdrGetModuleHandle(L"Core.dll"), "?PushBack@L2ParamStack@@QAEHPA_W@Z");
    L2StackPushBackD = (void(__fastcall*)(L2ParamStack & stack, void* dummy, int val))Utils::FindExport(Utils::LdrGetModuleHandle(L"Core.dll"), "?PushBack@L2ParamStack@@QAEHPAX@Z");
    if (!L2StackPushBackD) L2StackPushBackDH5 = (void(__fastcall*)(L2ParamStack & stack, void* dummy, __int64 val))Utils::FindExport(Utils::LdrGetModuleHandle(L"Core.dll"), "?PushBack@L2ParamStack@@QAEH_J@Z");
    L2StackDestructor = (void(__fastcall*)(L2ParamStack & stack))Utils::FindExport(Utils::LdrGetModuleHandle(L"Core.dll"), "??1L2ParamStack@@QAE@XZ");
}

L2ParamStackWrapper::L2ParamStackWrapper(size_t initialDwordsNum)
{
    staticInstance.L2StackConstructor(localStack, 0, initialDwordsNum);
}

void L2ParamStackWrapper::PushBack(void* val)
{
    staticInstance.L2StackPushBackV(localStack, 0, val);
}

void L2ParamStackWrapper::PushBack(int val)
{
    staticInstance.L2StackPushBackD ? staticInstance.L2StackPushBackD(localStack, 0, val) : staticInstance.L2StackPushBackDH5(localStack, 0, val);
}

L2ParamStack& L2ParamStackWrapper::Get()
{
    return localStack;
}

L2ParamStackWrapper::~L2ParamStackWrapper()
{
    staticInstance.L2StackDestructor(localStack);
}
