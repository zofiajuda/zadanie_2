using namespace std;
#include "MySignal.h"

TCanvas *create_Canvas(int num_his) // stworz canvas
{
    char *his = new char[10];
    sprintf(his, "%s%d", "canvas_", num_his);
    TCanvas *c1 = new TCanvas(his, his, 0, 0, 1028, 1028);

    return c1;
}

void zadanie_2(TString filename = "wave_0.dat")
{
    int nbins = 1024;
    // ##################################
    // initializitio of my class
    MySignal *signal = new MySignal();

    // ####################################
    // Create trees
    TFile *file = new TFile("signals.root", "RECREATE");
    TTree *tree = new TTree("signal_tree", "signal data");
    tree->Branch("mysignal", &signal);

    TH1F *hs = new TH1F("sygnal", "sygnal", nbins - 1, 0, 1023);
    // ###################################
    // Main function
    bool EndFile = false;
    int i = 0;
    fstream myfile;
    myfile.open(filename, ios::binary | ios::in);

    if (!myfile.is_open())
    {
        cout << "Unable to open file" << endl;
    }
    else
    {
        // ###############################
        // Loop over signals
        do
        {
            if (!myfile.eof())
            {

                // ##################################
                // Loop for reading one signal
                for (int j = 0; j < nbins; j++)
                {
                    //********************************
                    // Read binary and fill histo
                    // with corrected value in mV
                    float x;
                    myfile.read((char *)&x, sizeof(float));
                    hs->SetBinContent(j + 1, x / 4.096);
                    //********************************
                    // Calculate signal values
                    if (j == nbins - 1)
                    {
                        signal->CalcBaseline(hs, 50);
                        signal->ShiftBaseline(hs);
                        signal->CalcT0(hs, -25);
                        signal->CalcTot(hs);
                        signal->CalcAmplitude(hs);
                        signal->CalcCharge(hs, 250);
                        tree->Fill();
                        hs->Reset();
                    }
                }
            }
            else
            {
                EndFile = true;
            }
            i++;
        } while (!EndFile);
        tree->Write();
    }
    file->Close();
    delete signal;
}
void draw_histo(TString name_root_file = "signals.root", TString name_tree = "signal_tree")
{
    int nbins = 1024;

    MySignal *signal = new MySignal();
    // ##################################
    // Reading tree
    TFile *file = new TFile(name_root_file, "READ");
    auto tree = file->Get<TTree>(name_tree);
    tree->SetBranchAddress("mysignal", &signal);

    // ##################################
    // Initiate histograms
    TCanvas *c[5];
    TH1F *h[3];
    h[0] = new TH1F("amplituda", "amplituda; amplituda[mV]", 100, 0, 7000);
    h[1] = new TH1F("t0", "czas poczatkowy;t_{0} [ns]", 70, 0, 300);
    h[2] = new TH1F("ladunek", "ladunek;ladunek", 100, -8 * 10e3, 4 * 10e3);
    TH2F *ampvsch = new TH2F("ampvsch", "amplituda vs ladunek;amplituda [mV];ladunek", 50, 0, 700, 100, -8 * 10e3, 4 * 10e3);
    TH2F *chvt0 = new TH2F("chvt0", "ladunek vs czas poczatkowy;ladunek ;t0", 70, -8 * 10e3, 4 * 10e3, 70, 0, 300);

    // ##################################
    // Fill histograms
    int nentries = tree->GetEntries();

    for (int i = 0; i < nentries; i++)
    {

        tree->GetEntry(i);

        h[0]->Fill(signal->GetAmplitude());
        h[1]->Fill(signal->GetT0());
        h[2]->Fill(signal->GetCharge());
        ampvsch->Fill(signal->GetAmplitude(), signal->GetCharge());
        chvt0->Fill(signal->GetCharge(), signal->GetT0());
    }
    // file->Close();
    // ####################################
    //  Draw histograms

    TFile *file_histo = new TFile("histogramy.root", "RECREATE");
    gStyle->SetOptStat(0);
    for (int k = 0; k < 5; k++)
    {
        c[k] = create_Canvas(k);
        if (k < 3)
        {
            c[k]->cd();
            h[k]->Draw();
            c[k]->Write();
            h[k]->Write();
        }
    }
    c[3]->cd();
    ampvsch->Draw("colz");
    c[3]->Write();
    ampvsch->Write();
    c[4]->cd();
    chvt0->Draw("colz");
    c[4]->Write();
    chvt0->Write();
}