/*
* TLS Protocol Version Management
* (C) 2012 Jack Lloyd
*
* Released under the terms of the Botan license
*/

#ifndef BOTAN_TLS_PROTOCOL_VERSION_H__
#define BOTAN_TLS_PROTOCOL_VERSION_H__

#include <botan/get_byte.h>
#include <string>

namespace Botan {

namespace TLS {

/**
* TLS Protocol Version
*/
class BOTAN_DLL Protocol_Version
   {
   public:
      enum Version_Code {
         SSL_V3             = 0x0300,
         TLS_V10            = 0x0301,
         TLS_V11            = 0x0302,
         TLS_V12            = 0x0303
      };

      Protocol_Version() : m_version(0) {}

      /**
      * @param named_version a specific named version of the protocol
      */
      Protocol_Version(Version_Code named_version) :
         m_version(static_cast<u16bit>(named_version)) {}

      /**
      * @param major the major version
      * @param minor the minor version
      */
      Protocol_Version(byte major, byte minor) :
         m_version((static_cast<u16bit>(major) << 8) | minor) {}

      /**
      * @return true if this is a valid protocol version
      */
      bool valid() const { return (m_version != 0); }

      /**
      * @return major version of the protocol version
      */
      byte major_version() const { return get_byte(0, m_version); }

      /**
      * @return minor version of the protocol version
      */
      byte minor_version() const { return get_byte(1, m_version); }

      /**
      * @return human-readable description of this version
      */
      std::string to_string() const;

      /**
      * @return if this version is equal to other
      */
      bool operator==(const Protocol_Version& other) const
         {
         return (m_version == other.m_version);
         }

      /**
      * @return if this version is not equal to other
      */
      bool operator!=(const Protocol_Version& other) const
         {
         return (m_version != other.m_version);
         }

      /**
      * @return if this version is later than or equal to other
      */
      bool operator>=(const Protocol_Version& other) const
         {
         return (m_version >= other.m_version);
         }

      /**
      * @return if this version is later than other
      */
      bool operator>(const Protocol_Version& other) const
         {
         return (m_version > other.m_version);
         }

      /**
      * @return if this version is earlier than or equal to other
      */
      bool operator<=(const Protocol_Version& other) const
         {
         return (m_version <= other.m_version);
         }

      /**
      * @return if this version is earlier than other
      */
      bool operator<(const Protocol_Version& other) const
         {
         return (m_version < other.m_version);
         }

   private:
      u16bit m_version;
   };

}

}

#endif

