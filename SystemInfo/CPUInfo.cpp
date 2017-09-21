#include "CPUInfo.h"
#include "CacheDescriptors.h"
#include <string>

#define CHECK_BIT(var,pos) ((var) & (1<<(pos))
#define MASK_LOWBYTE(var)  ((var) & 0xff)


void CPUInfo::initCPUID()
{
	
	int32_t* startOfArray = registers.data(); //get the starting address of the array
	__cpuid(startOfArray, 0);
	MaxInputBasicCPUID = registers[0]; //number of standard CPUID leafs

	char vend[0x18] = {0}; //initialize a char array for the max length of the vendor string
	int count = 0;

	//per Intel documentation vendor name stored in ebx, edx, ecx -- need to switch order in array
	int32_t temp = registers[3]; //edx
	registers[3] = registers[2];
	registers[2] = temp;


	for(int i=1; i < 4; i++)
	{
		for(int j=0; j < 4; j++)
		{
			vend[count] = (char)registers[i]; // get the lowest order byte
			registers[i] = registers[i] >> 8;
			count++;
		}
	}
	vendor = vend;

	CPUIDExtended();
	startOfArray = nullptr; //clean dangling pointer
}


void CPUInfo::CPUIDExtended()
{
	std::array<int32_t,4> extendedRegisters;
	int32_t* startOfArray = extendedRegisters.data();

	int32_t extended = 0x80000000;
	__cpuid(startOfArray, extended);
	MaxInputExtendedCPUID  = extendedRegisters[0];

	for (int k = extended+1; k<MaxInputExtendedCPUID; k++)
	{
		__cpuid(startOfArray, k);
	}
}


int8_t CPUInfo::getStepping()
{
	__cpuid(registers.data(), 0x1); 
	return registers[0] & 0xf;
}

int8_t CPUInfo::getModel()
{
	__cpuid(registers.data(), 0x1);
	int8_t mod = (registers[0] & 0xf0) >> 4;
	return mod;
}

int8_t CPUInfo::getFamily()
{
	__cpuid(registers.data(), 0x1);
	return (registers[0] & 0xf00) >> 8;
}

uint16_t CPUInfo::getExtendedModel()
{
	int8_t family = getFamily();
	if(family == 0x6 || family == 0xf)
	{
		__cpuid(registers.data(), 0x1);
		uint32_t extMod = (registers[0] & 0xf0000) >> 12;
		uint16_t displayModel = extMod + getModel();
		while (displayModel & 0x1 == 0)
			displayModel >>= 1;
		return displayModel;
	}
	else return getModel();
}

std::array<int32_t, 4> CPUInfo::getCPUID(std::array<int32_t, 4> regs, int32_t eax, int32_t ecx)
{
	__cpuidex(regs.data(), eax, ecx);
	return regs;
}


uint32_t CPUInfo::getExtendedFamily()
{
	if (getFamily() != 0xf)
		return getFamily();
	else 
	{
		(getCPUID(registers, 0x1, 0x0));
		 uint32_t displayModel = registers[0] & 0xff00000 + getFamily();
		 while (displayModel & 0x1 == 0)
			 displayModel >>= 1;
		 return displayModel;
	}
}

std::string CPUInfo::getProcessorType()
{
	getCPUID(registers, 0x1, 0x0);
	int8_t type = (registers[0] & 0x3000) >> 0xC;
	if (type == 0b00) return "Original OEM Processor";
	else if (type == 0b01) return "Intel OverDrive Processor";
	else if (type == 0b10) return "Dual Processor";
	return "Intel Reserved";
}


std::string CPUInfo::getBrand()
{
	__cpuid(registers.data(), 0x80000000);
	if (registers[0] < 0x80000004) return NULL;
	
	const int CPUID_Leaves = 3;
	const int registersNeeded = 4;
	int encodedBrand[CPUID_Leaves][registersNeeded];

	for(int i = 0; i <= 2; i++)
	{
		__cpuid(registers.data(), i+ 0x80000002);

		for(int j=0;j<registersNeeded;j++)
			encodedBrand[i][j] = registers[j];
	}
	
	std::string brand = "";

	//outside loop for 3 exteneded CPUID leaves
	for(int ii=0; ii < 3; ii++)
	{
		//loop for the 4 registers at each leaf
		for(int jj=0; jj < 4; jj++)
		{
			//inner loop for 4 bytes in each register
			for(int kk=0; kk<4;kk++)
			{
				if(encodedBrand[ii][jj] == 0x20202020) continue; //skip over excessive empty space
				brand += MASK_LOWBYTE(encodedBrand[ii][jj]);
				encodedBrand[ii][jj] >>= 8;
			}
			
		}
	}
	return brand;

}

std::string CPUInfo::getCacheTopology()
{
	__cpuid(registers.data(), 2);
	uint32_t validCacheData = 0x80000000; //bit 31 of the register will be 0 iff there is a valid 1 byte cache descriptor
	
	uint8_t highestByte=0;
	uint8_t topMiddleByte=0;
	uint8_t botMiddleByte=0;
	uint8_t bottomByte=0;
	std::string cacheTopology;
	std::string cacheDescriptor="";
	for(int i=0; i<4; i++)
	{
		
		if (!CHECK_BIT(registers[i], 31)))
		{
			if (i != 0) bottomByte = MASK_LOWBYTE(registers[i]);
			registers[i] >>= 8;
			botMiddleByte = MASK_LOWBYTE(registers[i]);
			registers[i] >>= 8;
			topMiddleByte = MASK_LOWBYTE(registers[i]);
			registers[i] >>= 8;
			highestByte = MASK_LOWBYTE(registers[i]);
		}
		
		std::array<uint8_t, 4> cacheCodes = { highestByte ,topMiddleByte, botMiddleByte, bottomByte };
		for(int j=0; j < 4; j++)
		{
			if (cacheCodes[j] == 0xFF) 
				cacheTopology += getCacheInfo();
			else if (cacheCodes[j] != 0 && CacheLookup.find(cacheCodes[j]) != CacheLookup.end())
			{
				cacheDescriptor = CacheLookup.find(cacheCodes[j])->second + "\n";
				cacheTopology += cacheDescriptor;
			}
			
		}
	}
	return cacheTopology;
	
}


std::string CPUInfo::getCacheInfo()
{ 
	
	registers[0] = 0xffffffff;
	int count = 0;

	struct Cache /* Struct organized largest element to smallest element to minimize alignment padding */
	{
		int32_t numSets;
		uint32_t CacheSize;
		int16_t lineSize;
		int16_t linePartitions;
		int16_t lineAssociativity;
		int8_t level;
		int8_t type;
		bool selfInit;
		bool FullyAssoc;
		bool WriteBack;
		bool Inclusive;
		bool Mapping;
	};
	std::string cacheDescription = "";

	while (registers[0] != 0x0)
	{
		__cpuidex(registers.data(), 0x4, count); 
		Cache cache;
		cache.type = registers[0] & 0x1F;
		if (cache.type == 0) break; //no more cache levels
 		cache.level = ((registers[0] & 0xE0) >> 5); 
		cache.selfInit = registers[0] & 0x100;
		cache.FullyAssoc = registers[0] & 0x200;
		cache.lineSize = (registers[1] & 0xFFF) + 1;
		cache.linePartitions = ((registers[1] & 0x3FF000) >> 12)  + 1;
		cache.lineAssociativity = ((registers[1] & 0xFFC00000) >> 22) + 1;
		cache.numSets = (registers[2] & 0xFFFFFFFF) + 1;
		cache.WriteBack = registers[3] & 0x1;
		cache.Inclusive = registers[3] & 0x2;
		cache.Mapping = registers[3] & 0x4;

		cache.CacheSize = cache.lineAssociativity * cache.lineSize * cache.linePartitions * cache.numSets;
		int16_t numCores = ((registers[1] & 0xFFC00000) >> 22) + 1; //includes hyperthreaded cores
		while (numCores % 2 != 0) numCores++; //round-up to nearest power of 2 --> likely ok solution if cores disabled in BIOS
		if (HTT()) numCores >>= 1; //if hyperthreading, number of physical cores is half -- possible issue on AMD

		std::string postfix;
		int8_t cachepostfixCount = 0;

		while(cache.CacheSize >= 1024) //find out which is the best size abbreviation
		{
			cache.CacheSize >>= 10;
			cachepostfixCount++;
		}
	
		switch(cachepostfixCount)
		{
			case 1: 
				postfix = "KB ";
				break;
			case 2:
				postfix = "MB ";
				break;
			case 3: //unlikely to happen for a long time
				postfix = "GB ";
				break;
			default: postfix = " bytes ";
		}

		std::string type;
		switch(cache.type)
		{
			case 1:
				type = "Data Cache ";
				break;
			case 2:
				type = "Instruction Cache ";
				break;
			case 3:
				type = "Unified Cache ";
				break;
			default: type = ""; //Error
		}

		cacheDescription += (cache.type < 3 ? std::to_string(numCores) + "x " : "") + "L" + std::to_string(cache.level) + " " + type
			+ std::to_string(cache.CacheSize) + postfix + (cache.FullyAssoc ? " Fully-Associative" : std::to_string(cache.lineAssociativity) + "-Way\n");

		count++;
	}
	return cacheDescription;
}


















