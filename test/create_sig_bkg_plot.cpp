/**
A very general program that builds a plot for signal+background model and
background only model in the same canvas.
**/
#include <iostream>

#include "TString.h"
#include "TCanvas.h"
#include "TROOT.h"

#include "RooGlobalFunc.h"
#include "RooAddPdf.h"
#include "RooPlot.h"

#if (defined (STANDALONE) or defined (__CINT__) )
   #include "RscCombinedModel.h"
   #include "RscTotModel.h"
#else
   #include "PhysicsTools/RooStatsCms/interface/RscCombinedModel.h"
   #include "PhysicsTools/RooStatsCms/interface/RscTotModel.h"
#endif

int main(int argc, char** argv){

    // Parse input

    if (argc == 2 and TString(argv[1]).Contains("-h")){
        std::cout << "\ncreate_sig_bkg_plot:\n"
                  << "A very general program that builds a plot for signal+background model and"
                  << " background only model in the same canvas.\n";
        return 1;
        }

    if (argc != 3){
        std::cerr << "\nUsage:\n " << argv[0] << " card model\n\n";
        if (not TString(argv[1]).Contains("-h"))
            std::cerr << "\n  Type " << argv[0] << " -h for more details.\n\n";
        return 1;
        }

    gROOT->SetStyle("Plain");

    TString card_name(argv[1]);
    TString model_name(argv[2]);

    RooMsgService::instance().setGlobalKillBelow(RooMsgService::FATAL) ;

    // Get the model from the card
    RscCombinedModel model(card_name,model_name);

    RooMsgService::instance().setGlobalKillBelow(RooMsgService::DEBUG) ;

    // Create the plots, component per component
    for (int i=0;i<model.getSize();++i){
        TCanvas c;
        c.cd();
        RscTotModel* totm = model.getModel(i);
        RooAbsPdf* sb_model = totm->getPdf();
        RooRealVar* x= (RooRealVar*) (&(* totm->getVars())[0]);
        RooPlot* frame=x->frame();

        TString title(" "+model_name+" component ");
        title+=i;
        title+=" ";
        frame->SetTitle(title);
        frame->SetXTitle(x->GetName());
        frame->SetYTitle(" ");

        sb_model->plotOn(frame);
        sb_model->plotOn(frame,
                         RooFit::Components(totm->getExtendedBkgPdf()->GetName()),
                         RooFit::LineStyle(kDashed)) ;

        frame->Draw();

        TString plotname(model_name+"_component");
        plotname+=i;
        plotname+=".png";
        c.Print(plotname);
        }

    }
