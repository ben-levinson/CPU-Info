#include <iostream>
#include <string>
#ifndef map
#include <map>
#endif

#include "CPUInfo.h"

const std::map<int8_t, std::string> TO_HEX = 
{
	{10, "A"},
	{11, "B"},
	{12, "C"},
	{13, "D"},
	{14, "E"},
	{15, "F"}
};


void PrintISAExtensions(CPUInfo c)
{
	std::cout << "SSE3 Supported: " << (c.SSE3() ? "True" : "False") << std::endl;
	std::cout << "PCLMULQDQ Supported: " << (c.PCLMULQDQ() ? "True" : "False") << std::endl;
	std::cout << "DTES64 Supported: " << (c.DTES64() ? "True" : "False") << std::endl;
	std::cout << "MONITOR Supported: " << (c.MONITOR() ? "True" : "False") << std::endl;
	std::cout << "DS_CPL Supported: " << (c.DS_CPL() ? "True" : "False") << std::endl;
	std::cout << "VMX Supported: " << (c.VMX() ? "True" : "False") << std::endl;
	std::cout << "SMX Supported: " << (c.SMX() ? "True" : "False") << std::endl;
	std::cout << "EIST Supported: " << (c.EIST() ? "True" : "False") << std::endl;
	std::cout << "TM2 Supported: " << (c.TM2() ? "True" : "False") << std::endl;
	std::cout << "SSSE3 Supported: " << (c.SSSE3() ? "True" : "False") << std::endl;
	std::cout << "CNXT_ID Supported: " << (c.CNXT_ID() ? "True" : "False") << std::endl;
	std::cout << "SDBG Supported: " << (c.SDBG() ? "True" : "False") << std::endl;
	std::cout << "FMA Supported: " << (c.FMA() ? "True" : "False") << std::endl;
	std::cout << "CMPXCHG16B Supported: " << (c.CMPXCHG16B() ? "True" : "False") << std::endl;
	std::cout << "xTPR Supported: " << (c.xTPR() ? "True" : "False") << std::endl;
	std::cout << "PDCM Supported: " << (c.PDCM() ? "True" : "False") << std::endl;
	std::cout << "PCID Supported: " << (c.PCID() ? "True" : "False") << std::endl;
	std::cout << "DCA Supported: " << (c.DCA() ? "True" : "False") << std::endl;
	std::cout << "SSE4.1 Supported: " << (c.SSE41() ? "True" : "False") << std::endl;
	std::cout << "SSE4.2 Supported: " << (c.SSE42() ? "True" : "False") << std::endl;
	std::cout << "x2APIC Supported: " << (c.x2APIC() ? "True" : "False") << std::endl;
	std::cout << "MOVBE Supported: " << (c.MOVBE() ? "True" : "False") << std::endl;
	std::cout << "POPCNT Supported: " << (c.POPCNT() ? "True" : "False") << std::endl;
	std::cout << "TSC_Deadline Supported: " << (c.TSC_Deadline() ? "True" : "False") << std::endl;
	std::cout << "AESNI Supported: " << (c.AESNI() ? "True" : "False") << std::endl;
	std::cout << "XSAVE Supported: " << (c.XSAVE() ? "True" : "False") << std::endl;
	std::cout << "OSXSAVE Supported: " << (c.OSXSAVE() ? "True" : "False") << std::endl;
	std::cout << "AVX Supported: " << (c.AVX() ? "True" : "False") << std::endl;
	std::cout << "F16C Supported: " << (c.F16C() ? "True" : "False") << std::endl;
	std::cout << "RDRAND Supported: " << (c.RDRAND() ? "True" : "False") << std::endl;

	std::cout << "FPU Supported: " << (c.FPU() ? "True" : "False") << std::endl;
	std::cout << "VME Supported: " << (c.VME() ? "True" : "False") << std::endl;
	std::cout << "DE Supported: " << (c.DE() ? "True" : "False") << std::endl;
	std::cout << "PSE Supported: " << (c.PSE() ? "True" : "False") << std::endl;
	std::cout << "TSC Supported: " << (c.TSC() ? "True" : "False") << std::endl;
	std::cout << "MSR Supported: " << (c.MSR() ? "True" : "False") << std::endl;
	std::cout << "PAE Supported: " << (c.PAE() ? "True" : "False") << std::endl;
	std::cout << "MCE Supported: " << (c.MCE() ? "True" : "False") << std::endl;
	std::cout << "CX8 Supported: " << (c.CX8() ? "True" : "False") << std::endl;
	std::cout << "APIC Supported: " << (c.APIC() ? "True" : "False") << std::endl;
	std::cout << "SEP Supported: " << (c.SEP() ? "True" : "False") << std::endl;
	std::cout << "MTRR Supported: " << (c.MTRR() ? "True" : "False") << std::endl;
	std::cout << "PGE Supported: " << (c.PGE() ? "True" : "False") << std::endl;
	std::cout << "MCA Supported: " << (c.MCA() ? "True" : "False") << std::endl;
	std::cout << "CMOV Supported: " << (c.CMOV() ? "True" : "False") << std::endl;
	std::cout << "PAT Supported: " << (c.PAT() ? "True" : "False") << std::endl;
	std::cout << "PSE_36 Supported: " << (c.PSE_36() ? "True" : "False") << std::endl;
	std::cout << "PSN Supported: " << (c.PSN() ? "True" : "False") << std::endl;
	std::cout << "CLFSH Supported: " << (c.CLFSH() ? "True" : "False") << std::endl;
	std::cout << "DS Supported: " << (c.DS() ? "True" : "False") << std::endl;
	std::cout << "ACPI Supported: " << (c.ACPI() ? "True" : "False") << std::endl;
	std::cout << "MMX Supported: " << (c.MMX() ? "True" : "False") << std::endl;
	std::cout << "FXSR Supported: " << (c.FXSR() ? "True" : "False") << std::endl;
	std::cout << "SSE Supported: " << (c.SSE() ? "True" : "False") << std::endl;
	std::cout << "SSE2 Supported: " << (c.SSE2() ? "True" : "False") << std::endl;
	std::cout << "SS Supported: " << (c.SS() ? "True" : "False") << std::endl;
	std::cout << "HTT Supported: " << (c.HTT() ? "True" : "False") << std::endl;
	std::cout << "TM Supported: " << (c.TM() ? "True" : "False") << std::endl;
	std::cout << "PBE Supported: " << (c.PBE() ? "True" : "False") << std::endl;
}

int main()
{
	CPUInfo c;
	c.initCPUID();

	std::string CPU_WMI = "Win32_Processor";
	std::string Temp_WMI = "Win32_TemperatureProbe";

	std::cout << "Vendor: " << c.getVendor() << std::endl; 
	std::cout << "Processor: " << c.getBrand() << std::endl;
	std::cout << "Family: " << std::to_string(c.getFamily()) << std::endl; 
	std::cout << "Extended Family: " << std::to_string(c.getExtendedFamily()) << std::endl; 
	std::cout << "Model: " << (c.getModel() > 9 ? TO_HEX.find(c.getModel())->second : std::to_string(c.getModel())) << std::endl; //bug fix for where the model number corresponds to \n and even with std::hex it prints newline
	std::cout << "Extended Model: " << std::hex << std::uppercase << c.getExtendedModel() << std::endl;
	std::cout << "Stepping: " << std::to_string(c.getStepping()) << std::endl;
	std::cout << "Processor Type: " << c.getProcessorType() << std::endl;

	std::cout << "\nCache structure: " << "\n" << c.getCacheTopology() << std::endl;
	/*
	IWbemLocator* pLoc;
	IWbemServices* pSvc;
	IEnumWbemClassObject* pEnumerator;
	int value1;

	if (readWMI_CPUInfo(pLoc, pSvc, pEnumerator, value1, CPU_WMI)) return value1;
	WMI_Cleanup(pLoc, pSvc, pEnumerator);

	if (readWMI_TempInfo(pLoc, pSvc, pEnumerator, value1, Temp_WMI)) return value1;
	WMI_Cleanup(pLoc, pSvc, pEnumerator); */
	
	PrintISAExtensions(c);


	return 0;   

}
