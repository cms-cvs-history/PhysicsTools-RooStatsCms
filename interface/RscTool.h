// @(#)root/hist:$Id: RscTool.h,v 1.4 2009/05/15 09:55:43 dpiparo Exp $
// Author: Danilo.Piparo@cern.ch, Gregory.Schott@cern.ch   05/04/2008

/// RscTool : The mother class of the RooStatsCms Tools

/**
\class RscTool
$Revision: 1.4 $
$Date: 2009/05/15 09:55:43 $
\author D. Piparo (danilo.piparo<at>cern.ch), G. Schott (grgory.schott<at>cern.ch) - Universitaet Karlsruhe 
The mother class of the RooStatsCms Tools.
**/

#ifndef __RscTool__
#define __RscTool__

#include "TNamed.h"

class RscTool : public TNamed  {

  public:

    RscTool(const char* name,const  char* title, bool verbosity=true);

    /// Set the verbosity
    void setVerbosity(bool verbosity);

    /// get the verbosity
    bool is_verbose();

  private:

    /// Verbosity flag
    bool m_verbose;


//For Cint
#if (defined (STANDALONE) or defined (__CINT__) )
ClassDef(RscTool,1)
#endif
};

#endif
// Automatically converted from the standalone version Wed Apr 15 11:36:34 2009
