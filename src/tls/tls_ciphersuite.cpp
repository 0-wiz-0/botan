/*
* TLS Cipher Suite
* (C) 2004-2010,2012 Jack Lloyd
*
* Released under the terms of the Botan license
*/

#include <botan/tls_ciphersuite.h>
#include <botan/parsing.h>
#include <sstream>
#include <stdexcept>

namespace Botan {

namespace TLS {

Ciphersuite Ciphersuite::by_name(const std::string& name)
   {
   for(size_t i = 0; i != 65536; ++i)
      {
      Ciphersuite suite = Ciphersuite::by_id(i);

      if(!suite.valid())
         continue; // not a ciphersuite we know, skip

      if(suite.to_string() == name)
         return suite;
      }

   return Ciphersuite(); // some unknown ciphersuite
   }

bool Ciphersuite::psk_ciphersuite() const
   {
   return (kex_algo() == "PSK" ||
           kex_algo() == "DHE_PSK" ||
           kex_algo() == "ECDHE_PSK");
   }

bool Ciphersuite::ecc_ciphersuite() const
   {
   return (kex_algo() == "ECDH" || sig_algo() == "ECDSA");
   }

std::string Ciphersuite::to_string() const
   {
   if(m_cipher_keylen == 0)
      throw std::runtime_error("Ciphersuite::to_string - no value set");

   std::ostringstream out;

   out << "TLS_";

   if(kex_algo() != "RSA")
      {
      if(kex_algo() == "DH")
         out << "DHE";
      else if(kex_algo() == "ECDH")
         out << "ECDHE";
      else
         out << kex_algo();

      out << '_';
      }

   if(sig_algo() == "DSA")
      out << "DSS_";
   else if(sig_algo() != "")
      out << sig_algo() << '_';

   out << "WITH_";

   if(cipher_algo() == "ARC4")
      {
      out << "RC4_128_";
      }
   else
      {
      if(cipher_algo() == "3DES")
         out << "3DES_EDE";
      else if(cipher_algo() == "Camellia-128" || cipher_algo() == "Camellia-256")
         out << "CAMELLIA_" << std::to_string(8*cipher_keylen());
      else
         out << replace_char(cipher_algo(), '-', '_');

      out << "_CBC_";
      }

   if(mac_algo() == "SHA-1")
      out << "SHA";
   else if(mac_algo() == "SHA-256")
      out << "SHA256";
   else if(mac_algo() == "SHA-384")
      out << "SHA384";
   else
      out << mac_algo();

   return out.str();
   }

}

}

