#include <windows.h>
#pragma comment(lib,"Advapi32.lib") 

#define ProcessMitigationPolicy 52
typedef int ProcessInformationClass;
typedef NTSTATUS(NTAPI * _NtQueryInformationProcess)(
	HANDLE ProcessHandle,
	ProcessInformationClass  informationClass,
	PVOID ProcessInformation,
	ULONG ProcessInformationLength,
	PULONG ReturnLength
	);

typedef struct _PROCESS_MITIGATION_POLICY_INFORMATION
{
	PROCESS_MITIGATION_POLICY Policy;
	union
	{
		PROCESS_MITIGATION_ASLR_POLICY ASLRPolicy;
		PROCESS_MITIGATION_STRICT_HANDLE_CHECK_POLICY StrictHandleCheckPolicy;
		PROCESS_MITIGATION_SYSTEM_CALL_DISABLE_POLICY SystemCallDisablePolicy;
		PROCESS_MITIGATION_EXTENSION_POINT_DISABLE_POLICY ExtensionPointDisablePolicy;
		PROCESS_MITIGATION_DYNAMIC_CODE_POLICY DynamicCodePolicy;
//		PROCESS_MITIGATION_CONTROL_FLOW_GUARD_POLICY ControlFlowGuardPolicy;
		PROCESS_MITIGATION_BINARY_SIGNATURE_POLICY SignaturePolicy;
//		PROCESS_MITIGATION_FONT_DISABLE_POLICY FontDisablePolicy;
//		PROCESS_MITIGATION_IMAGE_LOAD_POLICY ImageLoadPolicy;
//		PROCESS_MITIGATION_SYSTEM_CALL_FILTER_POLICY SystemCallFilterPolicy;
//		PROCESS_MITIGATION_PAYLOAD_RESTRICTION_POLICY PayloadRestrictionPolicy;
//		PROCESS_MITIGATION_CHILD_PROCESS_POLICY ChildProcessPolicy;
//		PROCESS_MITIGATION_SIDE_CHANNEL_ISOLATION_POLICY SideChannelIsolationPolicy;
	};
} PROCESS_MITIGATION_POLICY_INFORMATION, *PPROCESS_MITIGATION_POLICY_INFORMATION;

BOOL EnableDebugPrivilege(BOOL fEnable)
{
	BOOL fOk = FALSE;
	HANDLE hToken;
	if (OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, &hToken))
	{
		TOKEN_PRIVILEGES tp;
		tp.PrivilegeCount = 1;
		LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &tp.Privileges[0].Luid);
		tp.Privileges[0].Attributes = fEnable ? SE_PRIVILEGE_ENABLED : 0;
		AdjustTokenPrivileges(hToken, FALSE, &tp, sizeof(tp), NULL, NULL);
		fOk = (GetLastError() == ERROR_SUCCESS);
		CloseHandle(hToken);
	}
	return(fOk);
}

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		printf("\nCheck the ProcessMitigationPolicy of the selected process.\n");
		printf("Usage:\n");
		printf("     %s <pid>\n", argv[0]);
		return 0;
	}
	
	if (!EnableDebugPrivilege(TRUE))
	{
		printf("[!] AdjustTokenPrivileges Failed.<%d>\n", GetLastError());
		return 0;
	}
	
	DWORD pid;
	sscanf_s(argv[1], "%d", &pid);
	printf("[*] TargetPID:%d\n", pid);

	HANDLE hProcess;
	hProcess = GetCurrentProcess();
	
	hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
	if (hProcess == NULL)
	{
		printf("[!] OpenProcess Failed.<%d>\n", GetLastError());
		return 0;
	}
	
	_NtQueryInformationProcess NtQueryInformationProcess = (_NtQueryInformationProcess)GetProcAddress(GetModuleHandleA("NtDll.dll"), "NtQueryInformationProcess");
	if (!NtQueryInformationProcess)
	{
		printf("[!] Could not find NtQueryInformationProcess entry point in NTDLL.DLL\n");
		return 0;
	}

	NTSTATUS status;
	PROCESS_MITIGATION_POLICY_INFORMATION policyInfo;
	
	policyInfo.Policy = ProcessASLRPolicy;
	status = NtQueryInformationProcess(hProcess, ProcessMitigationPolicy, &policyInfo, sizeof(PROCESS_MITIGATION_POLICY_INFORMATION), NULL);
	if (status < 0)
	{
		printf("[!] NtQueryInformationProcess error\n");
		return 0;
	}
	printf("ProcessASLRPolicy:\n");
	printf("   EnableBottomUpRandomization                %u\n", policyInfo.ASLRPolicy.EnableBottomUpRandomization);
	printf("   EnableForceRelocateImages                  %u\n", policyInfo.ASLRPolicy.EnableForceRelocateImages);
	printf("   EnableHighEntropy                          %u\n", policyInfo.ASLRPolicy.EnableHighEntropy);
	printf("   DisallowStrippedImages                     %u\n", policyInfo.ASLRPolicy.DisallowStrippedImages);

	policyInfo.Policy = ProcessStrictHandleCheckPolicy;
	status = NtQueryInformationProcess(hProcess, ProcessMitigationPolicy, &policyInfo, sizeof(PROCESS_MITIGATION_POLICY_INFORMATION), NULL);
	if (status < 0)
	{
		printf("[!] NtQueryInformationProcess error\n");
		return 0;
	}
	printf("ProcessStrictHandleCheckPolicy:\n");
	printf("   HandleExceptionsPermanentlyEnabled         %u\n", policyInfo.StrictHandleCheckPolicy.HandleExceptionsPermanentlyEnabled);
	printf("   RaiseExceptionOnInvalidHandleReference     %u\n", policyInfo.StrictHandleCheckPolicy.RaiseExceptionOnInvalidHandleReference);

	policyInfo.Policy = ProcessSystemCallDisablePolicy;
	status = NtQueryInformationProcess(hProcess, ProcessMitigationPolicy, &policyInfo, sizeof(PROCESS_MITIGATION_POLICY_INFORMATION), NULL);
	if (status < 0)
	{
		printf("[!] NtQueryInformationProcess error\n");
		return 0;
	}
	printf("ProcessSystemCallDisablePolicy:\n");
	printf("   DisallowWin32kSystemCalls                  %u\n", policyInfo.SystemCallDisablePolicy.DisallowWin32kSystemCalls);

	policyInfo.Policy = ProcessExtensionPointDisablePolicy;
	status = NtQueryInformationProcess(hProcess, ProcessMitigationPolicy, &policyInfo, sizeof(PROCESS_MITIGATION_POLICY_INFORMATION), NULL);
	if (status < 0)
	{
		printf("[!] NtQueryInformationProcess error\n");
		return 0;
	}
	printf("ProcessExtensionPointDisablePolicy:\n");
	printf("   DisableExtensionPoints                     %u\n", policyInfo.ExtensionPointDisablePolicy.DisableExtensionPoints);

	policyInfo.Policy = ProcessDynamicCodePolicy;
	status = NtQueryInformationProcess(hProcess, ProcessMitigationPolicy, &policyInfo, sizeof(PROCESS_MITIGATION_POLICY_INFORMATION), NULL);
	if (status < 0)
	{
		printf("[!] NtQueryInformationProcess error\n");
		return 0;
	}
	printf("ProcessDynamicCodePolicy:\n");
	printf("   ProhibitDynamicCode                        %u\n", policyInfo.DynamicCodePolicy.ProhibitDynamicCode);

	policyInfo.Policy = ProcessSignaturePolicy;
	status = NtQueryInformationProcess(hProcess, ProcessMitigationPolicy, &policyInfo, sizeof(PROCESS_MITIGATION_POLICY_INFORMATION), NULL);
	if (status < 0)
	{
		printf("[!] NtQueryInformationProcess error\n");
		return 0;
	}
	printf("ProcessSignaturePolicy:\n");
	printf("   MicrosoftSignedOnly                        %u\n", policyInfo.SignaturePolicy.MicrosoftSignedOnly);

	return 0;
}
