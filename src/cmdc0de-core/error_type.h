#pragma once


#include <string>
#include <map>

namespace cmdc0decore {

/**
*	interface to support facility specific error messages
*/
class ErrStrHandler {
public:
	ErrStrHandler() {}
	virtual ~ErrStrHandler() {}
	virtual const char *getErrorString(uint16_t errorCode)=0;
};

/**
 *	@Author Demetrius Comes
 *
 *  This struct is can be treated as boolean value
 *	This provides a structured type for
 *  representing success and failure.
 *
 *  This struct should never be expanded to have non-scalar
 *  types or virtual functions; we want to keep this very
 *  simple and light so it can act as value-like as possible.
 *
 *	<B>This class can carry an OS error as well as an application error
 *	giving us two levels </B>.  You can have a general application error, then
 *	by the checking the OSError you can give the actual error
 *
 *	<b>Think of this class as a boolean on steroids meaning it can be treated
 *	as a boolean return value, but if you want to know about the error in more detail
 *	you can.
 *	</B>
 */
struct ErrorType {
public:
   /**
    *  class of error codes, 256 codes to a class
    */
   enum Facility
   {
      FacilityGeneral				  = 0x0000, //general error
      FacilityOS					  = 0x0100, //error is OS level
      FacilityPersistence		      = 0x0200, //error is from the Persistence
	  FacilityEncomp				  = 0x0300,	//error is from Encode/Compress
   };

   // specific universal error codes
   enum
   {
      codeNone				= (FacilityGeneral | 0x00),
      codeOSSpecific		= (FacilityOS      | 0x00),
	  UNKNOWN_BOOLEAN_ERROR	= (FacilityGeneral | 0x00FF)
   };
public:
   /**
    *  constructor
    */
	ErrorType(uint16_t nError = 0, uint32_t nOSError = 0) : mnSClientError(nError), mnOSError(nOSError) {
	}
	/**
	* @date  10/23/2003 2:26:05 PM
	* @param  const ErrorType &r
	*
	*
	*/
	ErrorType(const ErrorType &r) {
		(*this)=r;
	}
	/**
	* @date  10/23/2003 2:26:03 PM
	* @return  ErrorType &
	* @param  const ErrorType &r
	*
	*
	*/
	ErrorType &operator=(const ErrorType &r) {
		mnSClientError = r.mnSClientError;
		mnOSError = r.mnOSError;
		return (*this);
	}

	/**
	* @date  2/2/2005 11:54:50 AM
	* @return  bool
	* @param  const ErrorType &r
	*
	*
	*/
	bool operator==(const ErrorType &r) {
		return (mnSClientError== r.mnSClientError && mnOSError == r.mnOSError);
	}

	/**
	* @date  10/23/2003 2:18:12 PM
	* @param  bool b
	*
	*	if false means no error and initialize as no error
	*	if true initialize to UNKNOWN_BOOLEAN_ERROR
	*/
	explicit ErrorType(bool b) : mnSClientError(0), mnOSError(0) {
		if(b) {
			mnSClientError = UNKNOWN_BOOLEAN_ERROR;
		}
	}

   /**
    *  test to see if there is an error
    */
	bool ok() const {return (mnSClientError == 0);}
	operator bool() const { return ok();}
	bool operator!() const {return !ok();}

	/**
	* @date  11/6/2003 12:48:10 PM
	* @return  std::string
	*
	*
	*/
	std::string getOSErrorString() const;
	/**
	* @date  11/6/2003 12:49:50 PM
	* @return  std::string
	* @param  int nError
	*
	*  static version
	*/
	static std::string getOSErrorString(uint32_t nError);
	/**
	* @date  9/15/2004 12:27:43 PM
	* @return  void
	* @param  std::string &errStr
	*
	*
	*/
	void getApplicationErrorString(std::string &errStr) const;

	// ok, just handle it all!
	void getErrorString(std::string &errStr) const {
		errStr.resize(0);
		if( getErrorFacility()==FacilityOS ) {
			errStr = getOSErrorString();
		}
		else {
			getApplicationErrorString(errStr);
		}
	}

	/**
    *  get the class of the error to localize it to a module
    */
   Facility getErrorFacility() const {return static_cast<Facility>(mnSClientError & 0xFF00);}

   bool isOsError() const {return (getErrorFacility()==FacilityOS);}

   ///returns the lower byte
   uint32_t getError() const {
	   if(getErrorFacility()==FacilityOS) {
		   return mnOSError;
	   } else {
			return mnSClientError;
	   }
   }

   // so we can return whole error at once
   // want this to be able to pass error back from C++ to C
   uint16_t getClientError() const {return mnSClientError;}

   uint32_t getOSError() const {return mnOSError;}

   /**
    *  create a "everything is fine" error code
    */
   static ErrorType noError() {return ErrorType(static_cast<uint16_t>(codeNone));}

	/**
	* @date  12/14/2004 1:30:14 PM
	* @return  void
	* @param  uint32 facility
	* @param  ErrStrHandler *facErrStrHandler
	*
	*
	*/
   static void addHandler(uint32_t facility, ErrStrHandler *facErrStrHandler);
	/**
	* @date  12/14/2004 1:30:16 PM
	* @return  void
	* @param  uint32 facility
	*
	*
	*/
   static void removeHandler(uint32_t facility);
private:
   /**
    *  Actual error code
    */
   uint16_t mnSClientError;
   /**
    *  os specific error code
    */
   uint32_t mnOSError;

   static std::map<uint32_t, ErrStrHandler *> mESHandlerMap;
};

}


