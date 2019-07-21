#pragma once

class L2ParamStack
{
	char unk[100];
};

class L2ParamStackWrapper
{

	class L2ParamStackStatic
	{

	public:

		L2ParamStackStatic();
		void(__fastcall* L2StackConstructor)(L2ParamStack& stack, void* dummy, size_t initialDwordsNum);
		void(__fastcall* L2StackPushBackV)(L2ParamStack& stack, void* dummy, void* val);
		void(__fastcall* L2StackPushBackD)(L2ParamStack& stack, void* dummy, int val);
		void(__fastcall* L2StackPushBackDH5)(L2ParamStack& stack, void* dummy, __int64 val);
		void(__fastcall* L2StackDestructor)(L2ParamStack& stack);

	};

	static L2ParamStackStatic staticInstance;
	L2ParamStack localStack;

public:

	L2ParamStackWrapper()
		:L2ParamStackWrapper(10) {}
	L2ParamStackWrapper(size_t initialDwordsNum);
	~L2ParamStackWrapper();

	void PushBack(void* val);
	void PushBack(int val);
	L2ParamStack& Get();
};