#ifndef DataFormats_LTCDigi_h
#define DataFormats_LTCDigi_h

#include <vector>

#include "boost/cstdint.hpp"

/** \class LTCDigi
 *  Data from the Local Trigger Controller (LTC)
 *
 * $Id$
 */

class LTCDigi
{
 public:
  // need a default constructor!
  LTCDigi() {}
  LTCDigi(const unsigned char* data);
  // These are to allow the event builder to grab the run number 
  // from a butter it knows points at LTC data.
  static uint32_t GetEventNumberFromBuffer(const unsigned char *databuffer) ;
  static uint32_t  GetRunNumberFromBuffer(const unsigned char *databuffer) ;
 public:
  // right now these are just silly but maybe if we pack the internals
  // then this won't seem as silly
  unsigned int eventNumber() const { return eventNumber_; };
  unsigned int eventID() const { return eventID_; };
  unsigned int runNumber() const   { return runNumber_;   };

  unsigned int bunchNumber() const { return bunchNumber_;};
  uint32_t     orbitNumber() const { return orbitNumber_;};

  int version() const { return versionNumber_; } ;
  int sourceID() const { return sourceID_; };

  int daqPartition() const { return daqPartition_; };

  uint32_t triggerInputStatus() const { return trigInputStat_; };
  uint32_t triggerInhibitNumber() const { return trigInhibitNumber_; };

  uint64_t bstGpsTime() const { return bstGpsTime_;};

  unsigned char bxMask() const { return ((triggerInputStatus()>>29)&0x1); } ;
  unsigned char vmeTrigger() const 
  { 
    return ((triggerInputStatus()>>28)&0x1); 
  } ;
  unsigned char ramTrigger() const 
  { 
    return ((triggerInputStatus()>>27)&0x1); 
  } ;
  unsigned char externTriggerMask() const
  { 
    return ((triggerInputStatus()>>20)&0xFFU); 
  } ;
  unsigned char cyclicTriggerMask() const
  { 
    return (triggerInputStatus()&0xFFU); 
  } ;
  
  
  
  bool HasTriggered( int i ) const {
    if ( i > 5 ) return false; // throw exception?
    return (externTriggerMask()&(0x1U<<i)!=0);
  }
 private:
  // unpacked for now
  unsigned int trigType_; // 4 bits

  unsigned int eventID_; // 24 bits
  unsigned int runNumber_; // 32 bits

  unsigned int sourceID_;    // 12 bits - 0xCBB constant for LTC

  unsigned int bunchNumber_; // 12 bits
  uint32_t     orbitNumber_; // 32 bits

  int          versionNumber_; // 8 bits - Slink data version number  

  int          daqPartition_;  // 4 bits
  
  uint32_t     eventNumber_; // 32 bits
                               // same as event number up to resets
  uint32_t     trigInputStat_; // 32 bits
  uint32_t     trigInhibitNumber_; // 32 bits
  uint64_t     bstGpsTime_; // 64 bits

  
    
};


typedef std::vector<LTCDigi> LTCDigiCollection;


#endif  // DataFormats_LTCDigi_h