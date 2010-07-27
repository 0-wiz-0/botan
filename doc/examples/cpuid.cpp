/*
* (C) 2009 Jack Lloyd
*
* Distributed under the terms of the Botan license
*/

#include <iostream>
#include <botan/cpuid.h>

using namespace Botan;

namespace {

void print_if_feature(const std::string& feature_name, bool exists)
   {
   std::cout << (exists ? '+' : '-') << " " << feature_name << "\n";
   }

}

int main()
   {
   CPUID::initialize();

   std::cout << "Cache line size = " << CPUID::cache_line_size() << "\n";

   print_if_feature("RDTSC", CPUID::has_rdtsc());
   print_if_feature("SSE2", CPUID::has_sse2());
   print_if_feature("SSSE3", CPUID::has_ssse3());
   print_if_feature("SSE4.1", CPUID::has_sse41());
   print_if_feature("SSE4.2", CPUID::has_sse42());
   print_if_feature("AVX", CPUID::has_avx());

   print_if_feature("MOVBE", CPUID::has_movbe());
   print_if_feature("PCMUL", CPUID::has_pcmuludq());
   print_if_feature("AES-NI", CPUID::has_aes_ni());

   print_if_feature("AltiVec", CPUID::has_altivec());
   }
