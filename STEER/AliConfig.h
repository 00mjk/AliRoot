#ifndef ALICONFIG_H
#define ALICONFIG_H
/* Copyright(c) 1998-1999, ALICE Experiment at CERN, All rights reserved. *
 * See cxx source for full Copyright notice                               */

/* $Id$ */
/* 
 * $Log$
 * Revision 1.4  2001/10/05 12:11:40  hristov
 * iostream.h used instead of iostream (HP)
 *
 * Revision 1.3  2001/10/04 15:30:56  hristov
 * Changes to accommodate the set of PHOS folders and tasks (Y.Schutz)
 *
 * Revision 1.2  2001/05/21 17:22:51  buncic
 * Fixed problem with missing AliConfig while reading galice.root
 *
 * Revision 1.1  2001/05/16 14:57:22  alibrary
 * New files for folders and Stack
 * 
 */

#include <iostream.h>
#include <TFolder.h>
#include <TList.h>
#include <TInterpreter.h>
#include <TROOT.h>
#include <TSystem.h>
#include <TDatabasePDG.h>
class TString ; 
class AliGenerator;
class AliModule;
class AliDetector;
class AliMC;
class AliConfig;
class AliTasks;

class AliConfig : public TNamed {
  
public:
  
  AliConfig(){ 
    // ctor: this is a singleton, the ctor should never be called but cint needs it as public
    cerr << "ERROR: AliConfig is a singleton default ctor not callable" << endl ;
    abort() ; 
  } 
  
  virtual ~ AliConfig (); 

  void       Add(TDatabasePDG *pdg);
  void       Add(char *list);
  
  void       Add(AliGenerator *generator,const char* eventfolder = fgkDefaultEventFolderName);
  void       Add (AliMC *mc,const char* eventfolder = fgkDefaultEventFolderName);
  void       Add (AliModule *module,const char* eventfolder = fgkDefaultEventFolderName);
  void       Add (AliDetector *detector,const char* eventfolder = fgkDefaultEventFolderName);

  Int_t      AddDetector(const char* evntfoldername,const char *name, const char* title);
  Int_t      AddDetector(TFolder* evntfolder,const char *name, const char* title);
  
  Int_t      CreateDetectorFolders(const char* evntfoldername,const char *name, const char* title);//Used by AliRunGetter
  Int_t      CreateDetectorFolders(TFolder* evntfolder,const char *name, const char* title);//Used by AliRunGetter
  Int_t      CreateDetectorTasks(const char *name, const char* title);
  
  static     AliConfig* Instance();
  
private:
  AliConfig(const char * name, const char * title );
  AliConfig(TFolder* top){};


  void          AddInFolder (const char * dir, TObject *obj);
  Int_t         AddSubTask(const char *taskname, const char* name, const char* title);
  Int_t         AddSubFolder(TFolder* topfolder, const char* infoler, //helper method
                     const char* newfoldname, const char* newfoldtitle);
  TObject*      FindInFolder (const char *dir, const char *name);
  
  // folders
  TFolder*              fTopFolder;

  static const TString  fgkPDGFolderName; 
  static const TString  fgkGeneratorFolderName; 
  static const TString  fgkMCFolderName;
  static const TString  fgkModuleFolderName;
  
  TString              *fDetectorTask;//!array with names for detector tasks
  TString              *fDetectorFolder;//!array with names for detector folders (where detector is going to be put)
  
  static AliConfig*     fInstance;
  
  
 public:

  TFolder*              BuildEventFolder(const char* name,const char* tilte);
  
  TFolder*              GetTopFolder();
  
  static const TString& GetModulesFolderName(){return fgkModuleFolderName;}
  
  const TString&        GetQATaskName() const; //returns path to QA tasks
  const TString&        GetDigitizerTaskName () const;
  const TString&        GetSDigitizerTaskName () const;
  const TString&        GetReconstructionerTaskName () const;
  const TString&        GetTrackerTaskName () const;
  
  
  const TString&        GetQAFolderName() const; //returns path to folder with QA output
  
  const TString&        GetDataFolderName();//returns name of data folder
  
  static const TString  fgkTopFolderName; //name of top AliRoot folder
 
  static const TString  fgkDefaultEventFolderName; 
  static const TString  fgkTasksFolderName;
  static const TString  fgkConstantsFolderName;
  
  static const TString  fgkDataFolderName;  
  static const TString  fgkConditionsFolderName;
  static const TString  fgkConfigurationFolderName;
  static const TString  fgkHeaderFolderName;
  
  static const TString  fgkDigitizerTaskName;
  static const TString  fgkSDigitizerTaskName;
  static const TString  fgkQATaskName;
  static const TString  fgkReconstructionerTaskName;
  static const TString  fgkTrackerTaskName;
  
  static const TString  fgkCalibrationFolderName;
  static const TString  fgkAligmentFolderName;
  static const TString  fgkQAFolderName;
  
  static const TString  fgkFieldFolderName;
  static const TString  fgkGeneratorsFolderName;
  static const TString  fgkVirtualMCFolderName;
   
  
  
  
  ClassDef(AliConfig,1) //Configuration class for AliRun
};				// end class AliConfig

#endif
