#pragma once

namespace Memory {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Zusammenfassung für Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	private:
		Int32 offeneKarten;
		Int32 spieler;
		array <Point> ^offeneKartenPos;
		array <Int32> ^paare;
		array <Int32,2> ^initSpielfeld;
		array <Int32,2> ^spielfeld;
	private: System::Windows::Forms::Label^  labelGewinner;
	private: System::Windows::Forms::Button^  buttonAufdecken;
	private: System::Windows::Forms::Timer^  timer2;
			 array <Point,2> ^aufgedeckt;

		Void karteOeffnen(Int32 x,Int32 y) {
				Int32 aufTemp=0;
				spielfeld[x,y]=initSpielfeld[x,y];
				offeneKartenPos[offeneKarten]=Point(x,y);

				if (aufgedeckt[spielfeld[x,y],0].X!=-1 && (aufgedeckt[spielfeld[x,y],0]!=Point(x,y)))
					aufTemp=1;

				aufgedeckt[spielfeld[x,y],aufTemp]=Point(x,y);
				offeneKarten++;
			}

		Void kartenSchliessen() {
			Boolean treffer=false;

			if (initSpielfeld[offeneKartenPos[0].X,offeneKartenPos[0].Y]==initSpielfeld[offeneKartenPos[1].X,offeneKartenPos[1].Y]) {
				spielfeld[offeneKartenPos[0].X,offeneKartenPos[0].Y]=21;
				spielfeld[offeneKartenPos[1].X,offeneKartenPos[1].Y]=21;

				for (Int32 schleife=0; schleife<2; schleife++)
					aufgedeckt[initSpielfeld[offeneKartenPos[schleife].X,offeneKartenPos[schleife].Y],schleife].X=-1;

				paare[spieler]++;
				treffer=true;
			}
			else {
				spielfeld[offeneKartenPos[0].X,offeneKartenPos[0].Y]=22;
				spielfeld[offeneKartenPos[1].X,offeneKartenPos[1].Y]=22;
			}
			offeneKarten=0;

			if ((paare[0]+paare[1])!=21) {
				if ((spieler==0 && treffer==false) || (spieler==1 && treffer==true)) {
					spieler=1;
					computerZug();
				}
			}
		}

		Void computerZug() {
			Int32 x1, y1, x2, y2;
			Boolean gefunden=false;
			Random ^zufallszahl=gcnew Random();

			for (Int32 schleife=0; schleife<21; schleife++) {
				if (aufgedeckt[schleife,0].X!=-1 && aufgedeckt[schleife,1].X!=-1) {
					x1=aufgedeckt[schleife,0].X;
					y1=aufgedeckt[schleife,0].Y;
					x2=aufgedeckt[schleife,1].X;
					y2=aufgedeckt[schleife,1].Y;
					gefunden=true;
				}
			}

			if (gefunden==true)
				karteOeffnen(x2,y2);
			else {
				do {
					x1=zufallszahl->Next(7);
					y1=zufallszahl->Next(6);
				} while (spielfeld[x1,y1]!=22);

				if (aufgedeckt[initSpielfeld[x1,y1],0].X!=-1 && (aufgedeckt[initSpielfeld[x1,y1],0]!=Point(x1,y1)))
					karteOeffnen(aufgedeckt[initSpielfeld[x1,y1],0].X,aufgedeckt[initSpielfeld[x1,y1],0].Y);
				else {
					do {
						x2=zufallszahl->Next(7);
						y2=zufallszahl->Next(6);
					} while (spielfeld[x2,y2]!=22 || (x1==x2 && y1==y2));
					karteOeffnen(x2,y2);
				}
			}

			karteOeffnen(x1,y1);
			tableLayoutPanel1->Refresh();
			timer1->Enabled=true;
		}
		

	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: Konstruktorcode hier hinzufügen.
			//

			Int32 bild = 0;
			array <Int32> ^feld=gcnew array <Int32>(42);
			Random ^zufallszahl;

			offeneKartenPos=gcnew array <Point>(2);
			paare=gcnew array <Int32>(2);
			initSpielfeld=gcnew array <Int32,2>(7,6);
			spielfeld=gcnew array <Int32,2>(7,6);
			aufgedeckt=gcnew array <Point,2>(21,2);

			spieler=0;
			paare[0]=0;
			paare[1]=0;

			for (Int32 schleife1=0; schleife1<21; schleife1++)
				for (Int32 schleife2=0; schleife2<2; schleife2++) 
					aufgedeckt[schleife1,schleife2]=Point(-1,-1);

			for (Int32 schleife=0; schleife<42; schleife++) {
				feld[schleife]=bild;
				if (((schleife+1)%2)==0)
					bild++;
			}

			zufallszahl=gcnew Random();

			for (Int32 schleife=0; schleife<42; schleife++) {
				Int32 temp1, temp2;
				temp1=zufallszahl->Next(42);
				temp2=feld[temp1];
				feld[temp1]=feld[schleife];
				feld[schleife]=temp2;
			}

			for (Int32 schleife1=0; schleife1<7; schleife1++)
				for (Int32 schleife2=0; schleife2<6; schleife2++) {
					initSpielfeld[schleife1,schleife2]=feld[schleife2*7+schleife1];
					spielfeld[schleife1,schleife2]=22;
				}

			
		}

	protected:
		/// <summary>
		/// Verwendete Ressourcen bereinigen.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel1;
	private: System::Windows::Forms::ImageList^  imageList1;
	private: System::Windows::Forms::Timer^  timer1;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  labelPaareMensch;
	private: System::Windows::Forms::Label^  labelPaareComputer;
	private: System::ComponentModel::IContainer^  components;
	protected: 

	private:
		/// <summary>
		/// Erforderliche Designervariable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Erforderliche Methode für die Designerunterstützung.
		/// Der Inhalt der Methode darf nicht mit dem Code-Editor geändert werden.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Form1::typeid));
			this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->imageList1 = (gcnew System::Windows::Forms::ImageList(this->components));
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->labelPaareMensch = (gcnew System::Windows::Forms::Label());
			this->labelPaareComputer = (gcnew System::Windows::Forms::Label());
			this->labelGewinner = (gcnew System::Windows::Forms::Label());
			this->buttonAufdecken = (gcnew System::Windows::Forms::Button());
			this->timer2 = (gcnew System::Windows::Forms::Timer(this->components));
			this->SuspendLayout();
			// 
			// tableLayoutPanel1
			// 
			this->tableLayoutPanel1->ColumnCount = 7;
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute, 
				64)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute, 
				64)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute, 
				64)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute, 
				64)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute, 
				64)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute, 
				64)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute, 
				64)));
			this->tableLayoutPanel1->Location = System::Drawing::Point(0, 0);
			this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
			this->tableLayoutPanel1->RowCount = 6;
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 64)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 64)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 64)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 64)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 64)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 64)));
			this->tableLayoutPanel1->Size = System::Drawing::Size(448, 384);
			this->tableLayoutPanel1->TabIndex = 0;
			this->tableLayoutPanel1->CellPaint += gcnew System::Windows::Forms::TableLayoutCellPaintEventHandler(this, &Form1::tableLayoutPanel1_CellPaint);
			this->tableLayoutPanel1->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::tableLayoutPanel1_MouseClick);
			// 
			// imageList1
			// 
			this->imageList1->ImageStream = (cli::safe_cast<System::Windows::Forms::ImageListStreamer^  >(resources->GetObject(L"imageList1.ImageStream")));
			this->imageList1->TransparentColor = System::Drawing::Color::Transparent;
			this->imageList1->Images->SetKeyName(0, L"apfel.bmp");
			this->imageList1->Images->SetKeyName(1, L"birne.bmp");
			this->imageList1->Images->SetKeyName(2, L"blume.bmp");
			this->imageList1->Images->SetKeyName(3, L"blume2.bmp");
			this->imageList1->Images->SetKeyName(4, L"ente.bmp");
			this->imageList1->Images->SetKeyName(5, L"fisch.bmp");
			this->imageList1->Images->SetKeyName(6, L"fuchs.bmp");
			this->imageList1->Images->SetKeyName(7, L"igel.bmp");
			this->imageList1->Images->SetKeyName(8, L"kaenguruh.bmp");
			this->imageList1->Images->SetKeyName(9, L"katze.bmp");
			this->imageList1->Images->SetKeyName(10, L"kuh.bmp");
			this->imageList1->Images->SetKeyName(11, L"maus1.bmp");
			this->imageList1->Images->SetKeyName(12, L"maus2.bmp");
			this->imageList1->Images->SetKeyName(13, L"maus3.bmp");
			this->imageList1->Images->SetKeyName(14, L"maus4.bmp");
			this->imageList1->Images->SetKeyName(15, L"melone.bmp");
			this->imageList1->Images->SetKeyName(16, L"pilz.bmp");
			this->imageList1->Images->SetKeyName(17, L"ronny.bmp");
			this->imageList1->Images->SetKeyName(18, L"schmetterling.bmp");
			this->imageList1->Images->SetKeyName(19, L"sonne.bmp");
			this->imageList1->Images->SetKeyName(20, L"wolke.bmp");
			this->imageList1->Images->SetKeyName(21, L"aufgedeckt.bmp");
			this->imageList1->Images->SetKeyName(22, L"verdeckt.bmp");
			// 
			// timer1
			// 
			this->timer1->Interval = 2000;
			this->timer1->Tick += gcnew System::EventHandler(this, &Form1::timer1_Tick);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(12, 387);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(45, 13);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Mensch";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(12, 415);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(52, 13);
			this->label2->TabIndex = 2;
			this->label2->Text = L"Computer";
			// 
			// labelPaareMensch
			// 
			this->labelPaareMensch->AutoSize = true;
			this->labelPaareMensch->Location = System::Drawing::Point(65, 387);
			this->labelPaareMensch->Name = L"labelPaareMensch";
			this->labelPaareMensch->Size = System::Drawing::Size(13, 13);
			this->labelPaareMensch->TabIndex = 3;
			this->labelPaareMensch->Text = L"0";
			// 
			// labelPaareComputer
			// 
			this->labelPaareComputer->AutoSize = true;
			this->labelPaareComputer->Location = System::Drawing::Point(65, 415);
			this->labelPaareComputer->Name = L"labelPaareComputer";
			this->labelPaareComputer->Size = System::Drawing::Size(13, 13);
			this->labelPaareComputer->TabIndex = 4;
			this->labelPaareComputer->Text = L"0";
			// 
			// labelGewinner
			// 
			this->labelGewinner->AutoSize = true;
			this->labelGewinner->Location = System::Drawing::Point(179, 387);
			this->labelGewinner->Name = L"labelGewinner";
			this->labelGewinner->Size = System::Drawing::Size(0, 13);
			this->labelGewinner->TabIndex = 5;
			// 
			// buttonAufdecken
			// 
			this->buttonAufdecken->Location = System::Drawing::Point(333, 387);
			this->buttonAufdecken->Name = L"buttonAufdecken";
			this->buttonAufdecken->Size = System::Drawing::Size(100, 21);
			this->buttonAufdecken->TabIndex = 6;
			this->buttonAufdecken->Text = L"Alles aufdecken";
			this->buttonAufdecken->UseVisualStyleBackColor = true;
			this->buttonAufdecken->Click += gcnew System::EventHandler(this, &Form1::buttonAufdecken_Click);
			// 
			// timer2
			// 
			this->timer2->Interval = 5000;
			this->timer2->Tick += gcnew System::EventHandler(this, &Form1::timer2_Tick);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(445, 437);
			this->Controls->Add(this->buttonAufdecken);
			this->Controls->Add(this->labelGewinner);
			this->Controls->Add(this->labelPaareComputer);
			this->Controls->Add(this->labelPaareMensch);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->tableLayoutPanel1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Fixed3D;
			this->MaximizeBox = false;
			this->Name = L"Form1";
			this->Text = L"Memory";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void tableLayoutPanel1_CellPaint(System::Object^  sender, System::Windows::Forms::TableLayoutCellPaintEventArgs^  e) {

				 imageList1->Draw(e->Graphics,Point(e->Column*64, e->Row*64), spielfeld[e->Column,e->Row]);
			 }
private: System::Void tableLayoutPanel1_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 
			 Int32 x=e->X/64;
			 Int32 y=e->Y/64;

			 if (offeneKarten==0 && spieler==1)
				 spieler=0;

			 if (offeneKarten==0 && spieler==0) {
				 if (spielfeld[x,y]==22)
					 karteOeffnen(x,y);
			 }
			 else
				 if (offeneKarten==1 && spieler==0)
					 if (spielfeld[x,y]==22) {
						 karteOeffnen(x,y);
						 timer1->Enabled=true;
					 }
					 tableLayoutPanel1->Refresh();
		 }
private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
			 timer1->Enabled=false;
			 kartenSchliessen();
			 labelPaareMensch->Text=Convert::ToString(paare[0]);
			 labelPaareComputer->Text=Convert::ToString(paare[1]);
			 tableLayoutPanel1->Refresh();
			
			 if (paare[0]+paare[1]==21) {
				 if (paare[0]>paare[1])
					 labelGewinner->Text="Der Mensch hat gewonnen!";
				 else if (paare[1]>paare[0])
					 labelGewinner->Text="Der Computer hat gewonnen!";
				 else
					 labelGewinner->Text="unentschieden!";
			 }
		 }
private: System::Void buttonAufdecken_Click(System::Object^  sender, System::EventArgs^  e) {

			if (timer1->Enabled==false) {
				for (Int32 x=0;x<7;x++) {
					for (Int32 y=0;y<6;y++){
						if (spielfeld[x,y]==22)
							 spielfeld[x,y]=initSpielfeld[x,y];
					}
				}
			tableLayoutPanel1->Refresh();
			}
			timer2->Enabled=true;
		 }
private: System::Void timer2_Tick(System::Object^  sender, System::EventArgs^  e) {
			 timer2->Enabled=false;
			 for (Int32 x=0;x<7;x++) {
					for (Int32 y=0;y<6;y++){
						if (spielfeld[x,y]!=21)
							 spielfeld[x,y]=22;
					}
				}
			 tableLayoutPanel1->Refresh();
		 }
};
}

