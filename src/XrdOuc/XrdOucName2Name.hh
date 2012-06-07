#ifndef __XRDOUCNAME2NAME_H__
#define __XRDOUCNAME2NAME_H__
/******************************************************************************/
/*                                                                            */
/*                    X r d O u c n a m e 2 n a m e . h h                     */
/*                                                                            */
/* (c) 2006 by the Board of Trustees of the Leland Stanford, Jr., University  */
/*                            All Rights Reserved                             */
/*   Produced by Andrew Hanushevsky for Stanford University under contract    */
/*              DE-AC02-76-SFO0515 with the Department of Energy              */
/******************************************************************************/

class XrdOucName2Name
{
public:

//------------------------------------------------------------------------------
//! Map a logical file name to a physical file name.
//!
//! @param  lfn   -> Logical file name.
//! @param  buff  -> Buffer where the physical file name of an existing file is
//!                  to be placed. It must end with a null byte.
//! @param  blen     The length of the buffer.
//!
//! @return Success: Zero.
//!         Failure: An errno number describing the failure; typically
//!                  EINVAL       - The supplied lfn is invalid.
//!                  ENAMETOOLONG - The buffer is too small for the pfn.
//------------------------------------------------------------------------------

virtual int lfn2pfn(const char *lfn, char *buff, int blen) = 0;

//------------------------------------------------------------------------------
//! Map a logical file name to the name the file would have in a remote storage
//! system (e.g. Mass Storage System at a remote location).
//!
//! @param  lfn   -> Logical file name.
//! @param  buff  -> Buffer where the remote file name is to be placed. It need
//!                  not actually exist in that location but could be created
//!                  there with that name. It must end with a null byte.
//! @param  blen     The length of the buffer.
//!
//! @return Success: Zero.
//!         Failure: An errno number describing the failure; typically
//!                  EINVAL       - The supplied lfn is invalid.
//!                  ENAMETOOLONG - The buffer is too small for the pfn.
//------------------------------------------------------------------------------

virtual int lfn2rfn(const char *lfn, char *buff, int blen) = 0;

//------------------------------------------------------------------------------
//! Map a physical file name to it's logical file name.
//!
//! @param  pfn   -> Physical file name. This is always a valid name of either
//!                  an existing file or a file that could been created.
//! @param  buff  -> Buffer where the logical file name is to be placed. It need
//!                  not actually exist but could be created with that name.
//!                  It must end with a null byte.
//! @param  blen     The length of the buffer.
//!
//! @return Success: Zero.
//!         Failure: An errno number describing the failure; typically
//!                  EINVAL       - The supplied lfn is invalid.
//!                  ENAMETOOLONG - The buffer is too small for the pfn.
//------------------------------------------------------------------------------

virtual int pfn2lfn(const char *pfn, char *buff, int blen) = 0;

//------------------------------------------------------------------------------
//! Constructor
//------------------------------------------------------------------------------

             XrdOucName2Name() {}

//------------------------------------------------------------------------------
//! Destructor
//------------------------------------------------------------------------------

virtual     ~XrdOucName2Name() {}
};

/******************************************************************************/
/*                    X r d O u c g e t N a m e 2 N a m e                     */
/******************************************************************************/
  
//------------------------------------------------------------------------------
//! Obtain an instance of the XrdOucName2Name object.
//!
//! This extern "C" function is called when a shared library plug-in containing
//! implementation of this class is loaded. It must exist in the shared library
//! and must be thread-safe.
//!
//! @param  eDest -> The error object that must be used to print any errors or
//!                  other messages (see XrdSysError.hh).
//! @param  confg -> Name of the configuration file that was used. This pointer
//!                  may be null though that would be impossible.
//! @param  parms -> Argument string specified on the namelib directive. It may
//!                  be null or point to a null string if no parms exist.
//! @param  lroot -> The path specified by the localroot directive. It is a
//!                  null pointer if the directive was not specified.
//! @param  rroot -> The path specified by the remoteroot directive. It is a
//!                  null pointer if the directive was not specified.
//!
//! @return Success: A pointer to an instance of the XrdOucName2Name object.
//!         Failure: A null pointer which causes initialization to fail.
//!
//! The Name2Name object is used frequently in the course of opening files
//! as well as other meta-file operations (e.g., stat(), rename(), etc.).
//! The algorithms used by this object *must* be efficient and speedy;
//! otherwise system performance will be severely degraded.
//------------------------------------------------------------------------------

class XrdSysError;

#define XrdOucgetName2NameArgs XrdSysError       *eDest, \
                               const char        *confg, \
                               const char        *parms, \
                               const char        *lroot, \
                               const char        *rroot

extern "C" XrdOucName2Name *XrdOucgetName2Name(XrdOucgetName2NameArgs);

//------------------------------------------------------------------------------
//! Declare compilation version.
//!
//! Additionally, you *should* declare the xrootd version you used to compile
//! your plug-in. While not currently required, it is highly recommended to
//! avoid execution issues should the class definition change. Declare it as:
//------------------------------------------------------------------------------

/*! #include "XrdVersion.hh"
    XrdVERSIONINFO(XrdOucgetName2Name,<name>);

    where <name> is a 1- to 15-character unquoted name identifying your plugin.
*/
#endif
