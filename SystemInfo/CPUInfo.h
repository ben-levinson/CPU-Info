#include <intrin.h> 
#include <array>
#include <vector>


class CPUInfo
{
public:
	void initCPUID();
	

	std::string getVendor() { return vendor; }
	std::string getBrand();
	int8_t getStepping();
	int8_t getModel(); 
	int8_t getFamily();
	std::string getProcessorType(); 
	uint16_t getExtendedModel();
	uint32_t getExtendedFamily();

	/* ISA extensions listed in ecx register */
	bool SSE3(void)		{ __cpuid(registers.data(), 1); return registers[2] & 0x1; }
	bool PCLMULQDQ(void){ __cpuid(registers.data(), 1); return registers[2] & (0x1 << 1); }
	bool DTES64(void)	{ __cpuid(registers.data(), 1); return registers[2] & (0x1 << 2); }
	bool MONITOR(void)	{ __cpuid(registers.data(), 1); return registers[2] & (0x1 << 3); }
	bool DS_CPL(void)	{ __cpuid(registers.data(), 1); return registers[2] & (0x1 << 4); }
	bool VMX(void)		{ __cpuid(registers.data(), 1); return registers[2] & (0x1 << 5); }
	bool SMX(void)		{ __cpuid(registers.data(), 1); return registers[2] & (0x1 << 6); }
	bool EIST(void)		{ __cpuid(registers.data(), 1); return registers[2] & (0x1 << 7); }
	bool TM2(void)		{ __cpuid(registers.data(), 1); return registers[2] & (0x1 << 8); }
	bool SSSE3(void)	{ __cpuid(registers.data(), 1); return registers[2] & (0x1 << 9); }
	bool CNXT_ID(void)  { __cpuid(registers.data(), 1); return registers[2] & (0x1 << 10); }
	bool SDBG(void)     { __cpuid(registers.data(), 1); return registers[2] & (0x1 << 11); }
	bool FMA(void)		{ __cpuid(registers.data(), 1); return registers[2] & (0x1 << 12); }
	bool CMPXCHG16B(void) { __cpuid(registers.data(), 1); return registers[2] & (0x1 << 13); }
	bool xTPR(void)		{ __cpuid(registers.data(), 1); return registers[2] & (0x1 << 14); }
	bool PDCM(void)		{ __cpuid(registers.data(), 1); return registers[2] & (0x1 << 15); }
	bool PCID(void)		{ __cpuid(registers.data(), 1); return registers[2] & (0x1 << 17); }
	bool DCA(void)		{ __cpuid(registers.data(), 1); return registers[2] & (0x1 << 18); }
	bool SSE41(void)	{ __cpuid(registers.data(), 1); return registers[2] & (0x1 << 19); }
	bool SSE42(void)	{ __cpuid(registers.data(), 1); return registers[2] & (0x1 << 20); }
	bool x2APIC(void)	{ __cpuid(registers.data(), 1); return registers[2] & (0x1 << 21); }
	bool MOVBE(void)	{ __cpuid(registers.data(), 1); return registers[2] & (0x1 << 22); }
	bool POPCNT(void)	{ __cpuid(registers.data(), 1); return registers[2] & (0x1 << 23); }
	bool TSC_Deadline(void) { __cpuid(registers.data(), 1); return registers[2] & (0x1 << 24); }
	bool AESNI(void)	{ __cpuid(registers.data(), 1); return registers[2] & (0x1 << 25); }
	bool XSAVE(void)	{ __cpuid(registers.data(), 1); return registers[2] & (0x1 << 26); }
	bool OSXSAVE(void)	{ __cpuid(registers.data(), 1); return registers[2] & (0x1 << 27); }
	bool AVX(void)		{ __cpuid(registers.data(), 1); return registers[2] & (0x1 << 28); }
	bool F16C(void)		{ __cpuid(registers.data(), 1); return registers[2] & (0x1 << 29); }
	bool RDRAND(void)	{ __cpuid(registers.data(), 1); return registers[2] & (0x1 << 30); }

	/* ISA extensions listed in edx register */
	bool FPU(void)		{ __cpuid(registers.data(), 1); return registers[3] & 0x1; }
	bool VME(void)		{ __cpuid(registers.data(), 1); return registers[3] & (0x1 << 1); }
	bool DE(void)		{ __cpuid(registers.data(), 1); return registers[3] & (0x1 << 2); }
	bool PSE(void)		{ __cpuid(registers.data(), 1); return registers[3] & (0x1 << 3); }
	bool TSC(void)		{ __cpuid(registers.data(), 1); return registers[3] & (0x1 << 4); }
	bool MSR(void)		{ __cpuid(registers.data(), 1); return registers[3] & (0x1 << 5); }
	bool PAE(void)		{ __cpuid(registers.data(), 1); return registers[3] & (0x1 << 6); }
	bool MCE(void)		{ __cpuid(registers.data(), 1); return registers[3] & (0x1 << 7); }
	bool CX8(void)		{ __cpuid(registers.data(), 1); return registers[3] & (0x1 << 8); }
	bool APIC(void)		{ __cpuid(registers.data(), 1); return registers[3] & (0x1 << 9); }
	bool SEP(void)		{ __cpuid(registers.data(), 1); return registers[3] & (0x1 << 11); }
	bool MTRR(void)		{ __cpuid(registers.data(), 1); return registers[3] & (0x1 << 12); }
	bool PGE(void)		{ __cpuid(registers.data(), 1); return registers[3] & (0x1 << 13); }
	bool MCA(void)		{ __cpuid(registers.data(), 1); return registers[3] & (0x1 << 14); }
	bool CMOV(void)		{ __cpuid(registers.data(), 1); return registers[3] & (0x1 << 15); }
	bool PAT(void)		{ __cpuid(registers.data(), 1); return registers[3] & (0x1 << 16); }
	bool PSE_36(void)	{ __cpuid(registers.data(), 1); return registers[3] & (0x1 << 17); }
	bool PSN(void)		{ __cpuid(registers.data(), 1); return registers[3] & (0x1 << 18); }
	bool CLFSH(void)	{ __cpuid(registers.data(), 1); return registers[3] & (0x1 << 19); }
	bool DS(void)		{ __cpuid(registers.data(), 1); return registers[3] & (0x1 << 21); }
	bool ACPI(void)		{ __cpuid(registers.data(), 1); return registers[3] & (0x1 << 22); }
	bool MMX(void)		{ __cpuid(registers.data(), 1); return registers[3] & (0x1 << 23); }
	bool FXSR(void)		{ __cpuid(registers.data(), 1); return registers[3] & (0x1 << 24); }
	bool SSE(void)		{ __cpuid(registers.data(), 1); return registers[3] & (0x1 << 25); }
	bool SSE2(void)		{ __cpuid(registers.data(), 1); return registers[3] & (0x1 << 26); }
	bool SS(void)		{ __cpuid(registers.data(), 1); return registers[3] & (0x1 << 27); }
	bool HTT(void)		{ __cpuid(registers.data(), 1); return registers[3] & (0x1 << 28); }
	bool TM(void)		{ __cpuid(registers.data(), 1); return registers[3] & (0x1 << 29); }
	bool PBE(void)		{ __cpuid(registers.data(), 1); return registers[3] & (0x1 << 31); }

	/* Extended Features */
	bool FSGSBASE(void) { __cpuidex(registers.data(), 7, 0); return registers[1] & (0x1 << 0); }
	bool SGX(void)		{ __cpuidex(registers.data(), 7, 0); return registers[1] & (0x1 << 2); }
	bool BMI1(void)		{ __cpuidex(registers.data(), 7, 0); return registers[1] & (0x1 << 3); }
	bool HLE(void)		{ __cpuidex(registers.data(), 7, 0); return registers[1] & (0x1 << 4); }
	bool AVX2(void)		{ __cpuidex(registers.data(), 7, 0); return registers[1] & (0x1 << 5); }
	bool BMI2(void)		{ __cpuidex(registers.data(), 7, 0); return registers[1] & (0x1 << 8); }
	bool RTM(void)		{ __cpuidex(registers.data(), 7, 0); return registers[1] & (0x1 << 11); }
	bool RDT_M(void)	{ __cpuidex(registers.data(), 7, 0); return registers[1] & (0x1 << 12); }
	bool MPX(void)		{ __cpuidex(registers.data(), 7, 0); return registers[1] & (0x1 << 14); }
	bool RDT_A(void)	{ __cpuidex(registers.data(), 7, 0); return registers[1] & (0x1 << 15); }
	bool RDSEED(void)	{ __cpuidex(registers.data(), 7, 0); return registers[1] & (0x1 << 18); }
	bool ADX(void)		{ __cpuidex(registers.data(), 7, 0); return registers[1] & (0x1 << 19); }
	bool SMAP(void)		{ __cpuidex(registers.data(), 7, 0); return registers[1] & (0x1 << 20); }
	bool IPT(void)		{ __cpuidex(registers.data(), 7, 0); return registers[1] & (0x1 << 25); }
	bool SHA(void)		{ __cpuidex(registers.data(), 7, 0); return registers[1] & (0x1 << 29); }

	
	
	/* Thermal and Power Management */
	bool DigitalTemp(void)	{ __cpuid(registers.data(), 6); return registers[0] & (0x1 << 0); }
	bool TurboBoost(void)	{ __cpuid(registers.data(), 6); return registers[0] & (0x1 << 1); }
	bool ARAT(void)			{ __cpuid(registers.data(), 6); return registers[0] & (0x1 << 2); }
	bool PLN(void)			{ __cpuid(registers.data(), 6); return registers[0] & (0x1 << 4); }
	bool ECMD(void)			{ __cpuid(registers.data(), 6); return registers[0] & (0x1 << 5); }
	bool PTM(void)			{ __cpuid(registers.data(), 6); return registers[0] & (0x1 << 6); }



	std::string getCacheTopology();


private:
	void CPUIDExtended();
	
	std::array<int32_t,4> getCPUID(std::array<int32_t, 4> regs, int32_t eax, int32_t ecx);
	std::string getCacheInfo();
	int MaxInputBasicCPUID;
	int MaxInputExtendedCPUID;

	std::array<int32_t, 4> registers; //will hold data from eax, ebx, ecx, edx

	std::string vendor;
	std::string brand;
};