#include <Windows.h>
#include <string>

#define UseErrPolicy(Name) ErrPolicy##Name
#define UseMajorPolicyGroup(Name) MajorPolicyGroup##Name
#define UseMinorPolicyGroup(Name) MinorPolicyGroup##Name
#define MakeErrMajorPolicy(Name) struct MajorPolicyGroup##Name
#define MakeErrMinorPolicy(Name, Major) struct MinorPolicyGroup##Name : UseMajorPolicyGroup(Major) {\
	using MajorPolicy = UseMajorPolicyGroup(Major);\
}
#define MakeErrPolicy(Name, Major, Minor) struct ErrPolicy##Name : UseMajorPolicyGroup(Major) {\
	using MajorPolicyGroup = UseMajorPolicyGroup(Major);\
	using MinorPolicyGroup = UseMinorPolicyGroup(Minor);\
}
#define MakeSetErr(ErrPolicyName, Code, Cate, Name, Desc) template<>\
constexpr int SetErrRet<UseErrPolicy(ErrPolicyName)> = _ErrorCore::_SetError<Code, Cate, Name, Desc>
using namespace std;

struct _ErrorInfo {
	DWORD ErrorCode;	//¥ÌŒÛ¬Î
	string ErrorCate;	//¥ÌŒÛÀ˘ Ù¿‡±
	string ErrorName;	//¥ÌŒÛ√˚≥∆
	string ErrorDescription;	//¥ÌŒÛ√Ë ˆ
};

struct _ErrorCore {
	_ErrorInfo ErrorInfo;
	template<DWORD ErrorCode, const char* Cate, const char* Name, const char* Desc>
	constexpr int _SetError() {
		ErrorInfo.ErrorCode = ErrorCode;
		ErrorInfo.ErrorCate = Cate;
		ErrorInfo.ErrorName = Name;
		ErrorInfo.ErrorDescription = Desc;
		return 0;
	}

	template<>
	constexpr int _SetError<0x00000000, NULL, NULL, NULL>() {
		return 0;
	}
};

template<class ErrPolicy>
constexpr int SetErrRet = _ErrorCore::_SetError<0x00000000, NULL, NULL, NULL>();
