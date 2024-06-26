// AboutDialog.cpp : implementation file
//

#include "stdafx.h"
#include "WECompressor.h"
#include "AboutDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDialog dialog


CAboutDialog::CAboutDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CAboutDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAboutDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CAboutDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAboutDialog, CDialog)
	//{{AFX_MSG_MAP(CAboutDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAboutDialog message handlers

BOOL CAboutDialog::OnInitDialog() 
{
	CString	tempStr;
	char sepa[] = "#";
	char stringTemp[2000];
	char *token;

	CDialog::OnInitDialog();
	
	CListBox* pList = (CListBox*) GetDlgItem(IDC_LIST_HELP);

	ASSERT(pList != NULL);

	if (pList != NULL)
	{
		pList->ResetContent();

		pList->AddString("This is beta version,near to release.");
		pList->AddString(" ");
		pList->AddString("Thanx to:");
		pList->AddString("- CARP for assistance and support in");
		pList->AddString("  PSX ASM decompress routine,");
		pList->AddString("  beta testing,ALL offset formats and");
		pList->AddString("  spanish translation.");
		pList->AddString("- ZeroCooler & PikaFlash for all logo.");
		pList->AddString("- Junior-Santista for portuguese translation.");
		pList->AddString("- Ronaldinho-33 for french translation.");
		pList->AddString("- Alex,Gege86,thommaso,Arakin,spina81,");
		pList->AddString("  for beta test.");
		pList->AddString(" ");		
		pList->AddString("For bugs & errors : walxer@tiscalinet.it");
		pList->AddString("06/10/2003 - CopyRight (C) Walxer");

		/*tempStr.LoadString(IDS_INFO_HELP1);
	
		strcpy(stringTemp, tempStr);
		// Establish string and get the first token:
		token = strtok(stringTemp, sepa );		
		while (token != NULL)
		{
			pList->AddString(token);
			/* Get next tok:
			token = strtok( NULL, sepa );
		}
		
		pList->AddString("Informazioni su WE Player Editor");
		pList->AddString("---------------------------------------------------");
		pList->AddString("");
		pList->AddString("Questo programma serve x aggiornare i files");
		pList->AddString("select.bin e slpm_8660.00 che contengono");
		pList->AddString("tutti i dati dei giocatori, gli ordinamenti dei");
		pList->AddString("numeri di maglia e i nomi dei giocatori.");
		pList->AddString("Tale aggiornameto viene fatto convertendo");
		pList->AddString("i dati contenuti nei files delle Memory Card,");
		pList->AddString("senza quindi bisogno di complicati editor,");
		pList->AddString("ma sfruttando proprio quello messo a");
		pList->AddString("disposizione nel gioco stesso.");
		pList->AddString("Per memorizzare con correttezza i dati");
		pList->AddString("nelle Memory Card, si deve seguire questo");
		pList->AddString("schema:");
		pList->AddString("- Creare i 22 giocatori e metterli nei 22");
		pList->AddString(" stock liberi della Memory Card (Ovviamente");
		pList->AddString(" se volete editare una squadra di ML i");
		pList->AddString(" giocatori riconosciuti saranno i primi 18).");
		pList->AddString(" Non dimenticare il nome e inserire i giocatori");
		pList->AddString(" seguendo lo stesso ordine per ruolo usato");
		pList->AddString(" dal gioco stesso, quindi a partire dal portiere");
		pList->AddString(" fino all'attaccante, e partend da sinistra");
		pList->AddString(" quando i giocatori rivestono gli stessi ruoli.");
		pList->AddString("- Inserire l'ordinamento dei numeri di maglia");
		pList->AddString("  dei giocatori al posto dell'EIRE, la prima");
		pList->AddString("  squadra national x inenderci.");
		pList->AddString("- Editare una strategia per la squadra da");
		pList->AddString("  inserire, salvarla al primo slot libero");
		pList->AddString("  nella Memory Card (dopo i 2 blocchi delle");
		pList->AddString("  opzioni) nel primo slot dei 15 disponibili");
		pList->AddString("  per le strategie. Non dimenticare pero'");
		pList->AddString("  di editare anche capitano, battitori di");
		pList->AddString("  rigori, punizioni e calci d'angolo.");
		pList->AddString("- Salvare il tutto su una Memory Card vuota,");
		pList->AddString("  che non contenga altro che queste cose.");
		pList->AddString("A questo punto siete pronti x la");
		pList->AddString("conversione, che avverra' in maniera");
		pList->AddString("automatica e rapida.");
		pList->AddString("Selezionate la squadra da sostituire, oltre");
		pList->AddString("ad aver ovviamente specificato i files da");
		pList->AddString("leggere (Memory Card) e da modificare");
		pList->AddString("(select.bin e slpm_8660.00), e scegliete");
		pList->AddString("cosa si desidera aggiornare nei 2 file da");
		pList->AddString("modificare (nomi, caratteristiche, ecc...).");
		pList->AddString("Completato questo aggiornameto, siete");
		pList->AddString("pronti x aggiornare il file immagine,");		
		pList->AddString("inserendo i 2 file alla posizione giusta");
		pList->AddString("con l'aiuto del mio programmino");
		pList->AddString("BIN Patcher 1.1.");
		pList->AddString("");
		pList->AddString("Walxer");
		pList->AddString("-----------");
		pList->AddString("walxer@tiscalinet.it");
		pList->AddString("http://walxer.winningeleven.com");*/
	}
	MessageBeep(MB_ICONINFORMATION);	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
