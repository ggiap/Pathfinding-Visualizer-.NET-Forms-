#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "Search.h"
#include "A_star.h"
#include "GreedyBestFS.h"
#include "Dijkstra.h"

#include <fstream>
#include <sstream>

void Run();
sf::RenderWindow window;

namespace PathfindingForm
{
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	int rows;
	int columns;
	bool allowDiagonalMovement = false;
	bool loadFromFile = false;
	string path;
	int algorithmChoice = 1;
	int heuristicChoice = 1;

	/// <summary>
	/// Summary for Main_Form
	/// </summary>
	public ref class Main_Form : public System::Windows::Forms::Form
	{
	public:
		
		Main_Form(void)
		{
			InitializeComponent();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Main_Form()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  Btn_Open;
	private: System::Windows::Forms::TextBox^  sizeX_textBox;
	private: System::Windows::Forms::Label^  dimensions_label;
	private: System::Windows::Forms::Label^  warning_label;
	private: System::Windows::Forms::TextBox^  sizeY_textBox;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog;
	private: System::Windows::Forms::ToolStrip^  toolStrip1;
	private: System::Windows::Forms::ToolStripButton^  toolStripLabel_OpenFile;
	private: System::Windows::Forms::CheckBox^  checkBox;
	private: System::Windows::Forms::GroupBox^  groupBoxAlg;
	private: System::Windows::Forms::RadioButton^  radioButtonDijkstra;
	private: System::Windows::Forms::RadioButton^  radioButtonAstar;
	private: System::Windows::Forms::RadioButton^  radioButtonGBFS;
	private: System::Windows::Forms::RadioButton^  radioButtonRand;
	private: System::Windows::Forms::GroupBox^  groupBoxHeuristic;
	private: System::Windows::Forms::RadioButton^  radioButtonEuclidean;
	private: System::Windows::Forms::RadioButton^  radioButtonChebyshev;
	private: System::Windows::Forms::RadioButton^  radioButtonManhattan;


	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Main_Form::typeid));
			this->Btn_Open = (gcnew System::Windows::Forms::Button());
			this->sizeX_textBox = (gcnew System::Windows::Forms::TextBox());
			this->dimensions_label = (gcnew System::Windows::Forms::Label());
			this->warning_label = (gcnew System::Windows::Forms::Label());
			this->sizeY_textBox = (gcnew System::Windows::Forms::TextBox());
			this->openFileDialog = (gcnew System::Windows::Forms::OpenFileDialog());
			this->toolStrip1 = (gcnew System::Windows::Forms::ToolStrip());
			this->toolStripLabel_OpenFile = (gcnew System::Windows::Forms::ToolStripButton());
			this->checkBox = (gcnew System::Windows::Forms::CheckBox());
			this->groupBoxAlg = (gcnew System::Windows::Forms::GroupBox());
			this->radioButtonDijkstra = (gcnew System::Windows::Forms::RadioButton());
			this->radioButtonAstar = (gcnew System::Windows::Forms::RadioButton());
			this->radioButtonGBFS = (gcnew System::Windows::Forms::RadioButton());
			this->radioButtonRand = (gcnew System::Windows::Forms::RadioButton());
			this->groupBoxHeuristic = (gcnew System::Windows::Forms::GroupBox());
			this->radioButtonEuclidean = (gcnew System::Windows::Forms::RadioButton());
			this->radioButtonChebyshev = (gcnew System::Windows::Forms::RadioButton());
			this->radioButtonManhattan = (gcnew System::Windows::Forms::RadioButton());
			this->toolStrip1->SuspendLayout();
			this->groupBoxAlg->SuspendLayout();
			this->groupBoxHeuristic->SuspendLayout();
			this->SuspendLayout();
			// 
			// Btn_Open
			// 
			this->Btn_Open->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->Btn_Open->Location = System::Drawing::Point(12, 169);
			this->Btn_Open->Name = L"Btn_Open";
			this->Btn_Open->Size = System::Drawing::Size(161, 23);
			this->Btn_Open->TabIndex = 0;
			this->Btn_Open->Text = L"Open";
			this->Btn_Open->UseVisualStyleBackColor = true;
			this->Btn_Open->Click += gcnew System::EventHandler(this, &Main_Form::Btn_Open_Click);
			// 
			// sizeX_textBox
			// 
			this->sizeX_textBox->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->sizeX_textBox->Location = System::Drawing::Point(154, 52);
			this->sizeX_textBox->Name = L"sizeX_textBox";
			this->sizeX_textBox->Size = System::Drawing::Size(90, 20);
			this->sizeX_textBox->TabIndex = 1;
			this->sizeX_textBox->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->sizeX_textBox->TextChanged += gcnew System::EventHandler(this, &Main_Form::sizeX_textBox_TextChanged);
			this->sizeX_textBox->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &Main_Form::sizeX_textBox_KeyPress);
			// 
			// dimensions_label
			// 
			this->dimensions_label->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->dimensions_label->AutoSize = true;
			this->dimensions_label->Location = System::Drawing::Point(19, 55);
			this->dimensions_label->Name = L"dimensions_label";
			this->dimensions_label->Size = System::Drawing::Size(129, 13);
			this->dimensions_label->TabIndex = 2;
			this->dimensions_label->Text = L"Map size(up to 130 x130):";
			this->dimensions_label->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// warning_label
			// 
			this->warning_label->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->warning_label->AutoSize = true;
			this->warning_label->Location = System::Drawing::Point(110, 9);
			this->warning_label->Name = L"warning_label";
			this->warning_label->Size = System::Drawing::Size(137, 39);
			this->warning_label->TabIndex = 3;
			this->warning_label->Text = L"WARNING! \r\nRows and columns must be\r\nequal to work properly.";
			this->warning_label->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// sizeY_textBox
			// 
			this->sizeY_textBox->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->sizeY_textBox->Location = System::Drawing::Point(246, 52);
			this->sizeY_textBox->Name = L"sizeY_textBox";
			this->sizeY_textBox->Size = System::Drawing::Size(90, 20);
			this->sizeY_textBox->TabIndex = 4;
			this->sizeY_textBox->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->sizeY_textBox->TextChanged += gcnew System::EventHandler(this, &Main_Form::sizeY_textBox_TextChanged);
			this->sizeY_textBox->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &Main_Form::sizeY_textBox_KeyPress);
			// 
			// openFileDialog
			// 
			this->openFileDialog->Filter = L"Text files|*.txt";
			this->openFileDialog->RestoreDirectory = true;
			// 
			// toolStrip1
			// 
			this->toolStrip1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->toolStrip1->Dock = System::Windows::Forms::DockStyle::None;
			this->toolStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->toolStripLabel_OpenFile });
			this->toolStrip1->Location = System::Drawing::Point(0, 0);
			this->toolStrip1->Name = L"toolStrip1";
			this->toolStrip1->Size = System::Drawing::Size(75, 25);
			this->toolStrip1->TabIndex = 5;
			this->toolStrip1->Text = L"toolStrip1";
			// 
			// toolStripLabel_OpenFile
			// 
			this->toolStripLabel_OpenFile->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->toolStripLabel_OpenFile->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->toolStripLabel_OpenFile->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"toolStripLabel_OpenFile.Image")));
			this->toolStripLabel_OpenFile->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripLabel_OpenFile->Name = L"toolStripLabel_OpenFile";
			this->toolStripLabel_OpenFile->Size = System::Drawing::Size(63, 22);
			this->toolStripLabel_OpenFile->Text = L"Open File";
			this->toolStripLabel_OpenFile->Click += gcnew System::EventHandler(this, &Main_Form::toolStripLabel_OpenFile_Click);
			// 
			// checkBox
			// 
			this->checkBox->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->checkBox->Location = System::Drawing::Point(179, 169);
			this->checkBox->Name = L"checkBox";
			this->checkBox->Size = System::Drawing::Size(162, 21);
			this->checkBox->TabIndex = 6;
			this->checkBox->Text = L"Allow diagonal movement";
			this->checkBox->UseVisualStyleBackColor = true;
			this->checkBox->CheckedChanged += gcnew System::EventHandler(this, &Main_Form::checkBox_CheckedChanged);
			// 
			// groupBoxAlg
			// 
			this->groupBoxAlg->Controls->Add(this->radioButtonDijkstra);
			this->groupBoxAlg->Controls->Add(this->radioButtonAstar);
			this->groupBoxAlg->Controls->Add(this->radioButtonGBFS);
			this->groupBoxAlg->Controls->Add(this->radioButtonRand);
			this->groupBoxAlg->Location = System::Drawing::Point(15, 78);
			this->groupBoxAlg->Name = L"groupBoxAlg";
			this->groupBoxAlg->Size = System::Drawing::Size(158, 85);
			this->groupBoxAlg->TabIndex = 7;
			this->groupBoxAlg->TabStop = false;
			this->groupBoxAlg->Text = L"Algorithm";
			// 
			// radioButtonDijkstra
			// 
			this->radioButtonDijkstra->AutoSize = true;
			this->radioButtonDijkstra->Location = System::Drawing::Point(92, 53);
			this->radioButtonDijkstra->Name = L"radioButtonDijkstra";
			this->radioButtonDijkstra->Size = System::Drawing::Size(60, 17);
			this->radioButtonDijkstra->TabIndex = 3;
			this->radioButtonDijkstra->Text = L"Dijkstra";
			this->radioButtonDijkstra->UseVisualStyleBackColor = true;
			this->radioButtonDijkstra->CheckedChanged += gcnew System::EventHandler(this, &Main_Form::radioButtonDijkstra_CheckedChanged);
			// 
			// radioButtonAstar
			// 
			this->radioButtonAstar->AutoSize = true;
			this->radioButtonAstar->Location = System::Drawing::Point(92, 20);
			this->radioButtonAstar->Name = L"radioButtonAstar";
			this->radioButtonAstar->Size = System::Drawing::Size(36, 17);
			this->radioButtonAstar->TabIndex = 2;
			this->radioButtonAstar->Text = L"A*";
			this->radioButtonAstar->UseVisualStyleBackColor = true;
			this->radioButtonAstar->CheckedChanged += gcnew System::EventHandler(this, &Main_Form::radioButtonAstar_CheckedChanged);
			// 
			// radioButtonGBFS
			// 
			this->radioButtonGBFS->AutoSize = true;
			this->radioButtonGBFS->Location = System::Drawing::Point(7, 53);
			this->radioButtonGBFS->Name = L"radioButtonGBFS";
			this->radioButtonGBFS->Size = System::Drawing::Size(79, 17);
			this->radioButtonGBFS->TabIndex = 1;
			this->radioButtonGBFS->Text = L"GreedyBFS";
			this->radioButtonGBFS->UseVisualStyleBackColor = true;
			this->radioButtonGBFS->CheckedChanged += gcnew System::EventHandler(this, &Main_Form::radioButtonGBFS_CheckedChanged);
			// 
			// radioButtonRand
			// 
			this->radioButtonRand->AutoSize = true;
			this->radioButtonRand->Checked = true;
			this->radioButtonRand->Location = System::Drawing::Point(7, 20);
			this->radioButtonRand->Name = L"radioButtonRand";
			this->radioButtonRand->Size = System::Drawing::Size(65, 17);
			this->radioButtonRand->TabIndex = 0;
			this->radioButtonRand->TabStop = true;
			this->radioButtonRand->Text = L"Random";
			this->radioButtonRand->UseVisualStyleBackColor = true;
			this->radioButtonRand->CheckedChanged += gcnew System::EventHandler(this, &Main_Form::radioButtonRand_CheckedChanged);
			// 
			// groupBoxHeuristic
			// 
			this->groupBoxHeuristic->Controls->Add(this->radioButtonEuclidean);
			this->groupBoxHeuristic->Controls->Add(this->radioButtonChebyshev);
			this->groupBoxHeuristic->Controls->Add(this->radioButtonManhattan);
			this->groupBoxHeuristic->Enabled = false;
			this->groupBoxHeuristic->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->groupBoxHeuristic->Location = System::Drawing::Point(179, 78);
			this->groupBoxHeuristic->Name = L"groupBoxHeuristic";
			this->groupBoxHeuristic->Size = System::Drawing::Size(158, 85);
			this->groupBoxHeuristic->TabIndex = 8;
			this->groupBoxHeuristic->TabStop = false;
			this->groupBoxHeuristic->Text = L"Heuristic";
			// 
			// radioButtonEuclidean
			// 
			this->radioButtonEuclidean->AutoSize = true;
			this->radioButtonEuclidean->Location = System::Drawing::Point(42, 66);
			this->radioButtonEuclidean->Name = L"radioButtonEuclidean";
			this->radioButtonEuclidean->Size = System::Drawing::Size(72, 17);
			this->radioButtonEuclidean->TabIndex = 2;
			this->radioButtonEuclidean->Text = L"Euclidean";
			this->radioButtonEuclidean->UseVisualStyleBackColor = true;
			this->radioButtonEuclidean->CheckedChanged += gcnew System::EventHandler(this, &Main_Form::radioButtonEuclidean_CheckedChanged);
			// 
			// radioButtonChebyshev
			// 
			this->radioButtonChebyshev->AutoSize = true;
			this->radioButtonChebyshev->Location = System::Drawing::Point(42, 43);
			this->radioButtonChebyshev->Name = L"radioButtonChebyshev";
			this->radioButtonChebyshev->Size = System::Drawing::Size(72, 17);
			this->radioButtonChebyshev->TabIndex = 1;
			this->radioButtonChebyshev->Text = L"Chebysev";
			this->radioButtonChebyshev->UseVisualStyleBackColor = true;
			this->radioButtonChebyshev->CheckedChanged += gcnew System::EventHandler(this, &Main_Form::radioButtonChebyshev_CheckedChanged);
			// 
			// radioButtonManhattan
			// 
			this->radioButtonManhattan->AutoSize = true;
			this->radioButtonManhattan->Checked = true;
			this->radioButtonManhattan->Location = System::Drawing::Point(42, 19);
			this->radioButtonManhattan->Name = L"radioButtonManhattan";
			this->radioButtonManhattan->Size = System::Drawing::Size(76, 17);
			this->radioButtonManhattan->TabIndex = 0;
			this->radioButtonManhattan->TabStop = true;
			this->radioButtonManhattan->Text = L"Manhattan";
			this->radioButtonManhattan->UseVisualStyleBackColor = true;
			this->radioButtonManhattan->CheckedChanged += gcnew System::EventHandler(this, &Main_Form::radioButtonManhattan_CheckedChanged);
			// 
			// Main_Form
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(348, 195);
			this->Controls->Add(this->groupBoxHeuristic);
			this->Controls->Add(this->groupBoxAlg);
			this->Controls->Add(this->checkBox);
			this->Controls->Add(this->toolStrip1);
			this->Controls->Add(this->sizeY_textBox);
			this->Controls->Add(this->warning_label);
			this->Controls->Add(this->dimensions_label);
			this->Controls->Add(this->sizeX_textBox);
			this->Controls->Add(this->Btn_Open);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MaximizeBox = false;
			this->Name = L"Main_Form";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Main_Form";
			this->toolStrip1->ResumeLayout(false);
			this->toolStrip1->PerformLayout();
			this->groupBoxAlg->ResumeLayout(false);
			this->groupBoxAlg->PerformLayout();
			this->groupBoxHeuristic->ResumeLayout(false);
			this->groupBoxHeuristic->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private:
		void MarshalString(String ^ s, string& os) {
			using namespace Runtime::InteropServices;
			const char* chars =
				(const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
			os = chars;
			Marshal::FreeHGlobal(IntPtr((void*)chars));
		}

		System::Void Btn_Open_Click(System::Object^  sender, System::EventArgs^  e)
		{
			if (sizeY_textBox->Text == String::Empty || sizeY_textBox->Text == "1") return;
			if (Convert::ToInt32(sizeY_textBox->Text) < 2 || Convert::ToInt32(sizeX_textBox->Text) < 2)
			{
				sizeX_textBox->Text = "2";
				sizeY_textBox->Text = "2";
			}
			rows = Convert::ToInt32(sizeX_textBox->Text);
			columns = Convert::ToInt32(sizeY_textBox->Text);
			sizeX_textBox->Clear();
			sizeY_textBox->Clear();
			if (rows == columns)
				Run();
			else
				MessageBox::Show("Rows and Columns must be equal!", " ", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}

		System::Void sizeX_textBox_TextChanged(System::Object^  sender, System::EventArgs^  e)
		{
			if (sizeX_textBox->Text == String::Empty)
			{
				sizeY_textBox->Text = String::Empty;
				return;
			}
			if (Convert::ToInt32(sizeX_textBox->Text) > 130)
				sizeX_textBox->Text = "130";

			sizeY_textBox->Text = sizeX_textBox->Text;
		}

		System::Void sizeY_textBox_TextChanged(System::Object^  sender, System::EventArgs^  e)
		{
			if (sizeY_textBox->Text == String::Empty)
			{
				sizeX_textBox->Text = String::Empty;
				return;
			}
			if (Convert::ToInt32(sizeY_textBox->Text) > 130)
				sizeY_textBox->Text = "130";

			sizeX_textBox->Text = sizeY_textBox->Text;
		}

		System::Void sizeX_textBox_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e)
		{
			if (!(Char::IsDigit(e->KeyChar)) && e->KeyChar != 8) 
				e->Handled = true;
		}

		System::Void sizeY_textBox_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e)
		{
			if (!(Char::IsDigit(e->KeyChar)) && e->KeyChar != 8)
				e->Handled = true;
		}

		System::Void toolStripLabel_OpenFile_Click(System::Object^  sender, System::EventArgs^  e)
		{
			rows = 0;
			columns = 0;
			loadFromFile = true;
			if (openFileDialog->ShowDialog() == PathfindingForm::DialogResult::OK)
			{
				MarshalString(openFileDialog->FileName, path);
				ifstream file(path);
				if (file.is_open())
				{
					vector<int> temp;
					string buffer, number;
					if (getline(file, buffer))
					{
						stringstream line(buffer);
						while (line >> number)
						{
							temp.push_back(stoi(number));
						}
						columns = temp.size();
						++rows;
					}
					while (getline(file, buffer))
						++rows;

					if (rows != columns)
					{
						MessageBox::Show("Rows and Columns must be equal!"," ",MessageBoxButtons::OK, MessageBoxIcon::Error);
						sizeX_textBox->Text = String::Empty;
					}
					else
					{
						if (rows == 0)
							MessageBox::Show("The file is empty!", " ", MessageBoxButtons::OK, MessageBoxIcon::Error);
						else
							sizeX_textBox->Text = rows.ToString();
					}
				}
			}
		}

		System::Void checkBox_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
		{
			allowDiagonalMovement = checkBox->Checked;
		}

		System::Void radioButtonAstar_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
		{
			groupBoxHeuristic->Enabled = true;
			algorithmChoice = Alg_Choice::Astar;
		}

		System::Void radioButtonRand_CheckedChanged(System::Object^  sender, System::EventArgs^  e) 
		{
			groupBoxHeuristic->Enabled = false;
			algorithmChoice = Alg_Choice::Random;
		}

		System::Void radioButtonGBFS_CheckedChanged(System::Object^  sender, System::EventArgs^  e) 
		{
			groupBoxHeuristic->Enabled = true;
			algorithmChoice = Alg_Choice::GreedyBFS;
		}

		System::Void radioButtonDijkstra_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
		{
			groupBoxHeuristic->Enabled = false;
			algorithmChoice = Alg_Choice::Dijkstra;
		}

		System::Void radioButtonManhattan_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
		{
			heuristicChoice = Heuristic_Choice::Manhattan;
		}

		System::Void radioButtonChebyshev_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
		{
			heuristicChoice = Heuristic_Choice::Chebyshev;
		}

		System::Void radioButtonEuclidean_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
		{
			heuristicChoice = Heuristic_Choice::Euclidean;
		}
		
};
}

Node* Init_start(Grid &grid)
{
	for (size_t i = 0; i < grid.nodes.size(); ++i)
	{
		if (grid.nodes.at(i).value == 0)
		{
			return &grid.nodes.at(i);
		}
	}
	return nullptr;
}

Node* Init_finish(Grid &grid)
{
	for (size_t i = grid.nodes.size() - 1; i > 0; --i)
	{
		if (grid.nodes.at(i).value == 0)
		{
			return &grid.nodes.at(i);
		}
	}
	return nullptr;
}

void Random_Search(Grid &grid, Node *start, Node *finish)
{
	for (auto i = grid.nodes.begin(); i != grid.nodes.end(); ++i)
	{
		if (i->nodeIndex != start->nodeIndex && i->nodeIndex != finish->nodeIndex)
			i->value == 0 ? i->cell.setFillColor(sf::Color::White) : i->cell.setFillColor(sf::Color::Magenta);
	}

	Search search(grid);
	search.Start(*start, *finish);

	while (!search.finished)
	{
		search.Step(window, PathfindingForm::allowDiagonalMovement);
	}
#ifdef _DEBUG
	cout << "Search done. Path length: " << search.iterations << endl;
#endif // _DEBUG

	for (auto &node : search.path)
	{
		if (node->value != 1 && node->nodeIndex != start->nodeIndex &&
			node->nodeIndex != finish->nodeIndex)
		{
			node->cell.setFillColor(sf::Color::Blue);
		}
	}
}

void A_Star(Grid &grid, Node *start, Node *finish, int heuristicChoice)
{
	for (auto i = grid.nodes.begin(); i != grid.nodes.end(); ++i)
	{
		if (i->nodeIndex != start->nodeIndex && i->nodeIndex != finish->nodeIndex)
			i->value == 0 ? i->cell.setFillColor(sf::Color::White) : i->cell.setFillColor(sf::Color::Magenta);
	}
	A_star a_star(grid, *start, *finish, PathfindingForm::heuristicChoice);
	a_star.Start_Search(window, PathfindingForm::allowDiagonalMovement);

	if (a_star.path.size() > 1)
	{
		for (auto &node : a_star.path)
			if (node->nodeIndex != start->nodeIndex &&
				node->nodeIndex != finish->nodeIndex)
				node->cell.setFillColor(sf::Color::Blue);
	}
	else
		printf("No path found!\n\n");
}

void Greedy_Best_FS(Grid &grid, Node *start, Node *finish)
{
	for (auto i = grid.nodes.begin(); i != grid.nodes.end(); ++i)
	{
		if (i->nodeIndex != start->nodeIndex && i->nodeIndex != finish->nodeIndex)
			i->value == 0 ? i->cell.setFillColor(sf::Color::White) : i->cell.setFillColor(sf::Color::Magenta);
	}

	GreedyBestFS bestFS(grid, *start, *finish, PathfindingForm::heuristicChoice);
	bestFS.Start_Search(window, PathfindingForm::allowDiagonalMovement);

	if (bestFS.path.size() > 1)
	{
		for (auto &node : bestFS.path)
			if (node->nodeIndex != start->nodeIndex &&
				node->nodeIndex != finish->nodeIndex)
				node->cell.setFillColor(sf::Color::Blue);
	}
	else
		printf("No path found!\n\n");
}

void Dijkstra_Search(Grid &grid, Node *start, Node *finish)
{
	for (auto i = grid.nodes.begin(); i != grid.nodes.end(); ++i)
	{
		if (i->nodeIndex != start->nodeIndex && i->nodeIndex != finish->nodeIndex)
			i->value == 0 ? i->cell.setFillColor(sf::Color::White) : i->cell.setFillColor(sf::Color::Magenta);
	}

	Dijkstra dijkstra(grid, *start, *finish);
	dijkstra.Start_Search(window, PathfindingForm::allowDiagonalMovement);

	if (dijkstra.path.size() > 1)
	{
		for (auto &node : dijkstra.path)
			if (node->nodeIndex != start->nodeIndex &&
				node->nodeIndex != finish->nodeIndex)
				node->cell.setFillColor(sf::Color::Blue);
	}
	else
		printf("No path found!\n\n");
}

void Run()
{
	window.create(sf::VideoMode(730, 650), "SFML", sf::Style::Titlebar | sf::Style::Close);
	window.setPosition(sf::Vector2i(400, 0));

	::Button startButton;
	startButton.buttonConfig(
		sf::Vector2f(80.0f, 25.0f),
		sf::Vector2f(650.0f, 0.0f),
		sf::Color(150, 150, 150, 255),
		"Start");

	::Button resetButton;
	resetButton.buttonConfig(
		sf::Vector2f(80.0f, 25.0f),
		sf::Vector2f(650.0f, 26.0f),
		sf::Color(150, 150, 150, 255),
		"Reset");
	

	vector<int> temp;
	vector<vector<int>> map;

	if (PathfindingForm::loadFromFile)
	{
		string buffer, number;
		ifstream file(PathfindingForm::path);
		if (file.is_open())
		{
			while (getline(file, buffer))
			{
				stringstream line(buffer);
				while (line >> number)
				{
					temp.push_back(stoi(number));		
				}
#ifdef _DEBUG
				for (auto num : temp)
					printf("%d ", num);
				puts("");
#endif // _DEBUG

				map.push_back(temp);
				temp.clear();
			}
		}
		PathfindingForm::loadFromFile = false;
	}
	else
	{
		temp = vector<int>(PathfindingForm::rows, 0);
		map = vector<vector<int>>(PathfindingForm::columns, temp);
	}
	
	Grid grid(map);
	Node *start = Init_start(grid);
	Node *finish = Init_finish(grid);
	
	if (start == nullptr || finish == nullptr || start->nodeIndex == finish->nodeIndex)
	{
		PathfindingForm::MessageBox::Show("Cannot solve this grid!", " ", PathfindingForm::MessageBoxButtons::OK, PathfindingForm::MessageBoxIcon::Error);
		window.close();
		return;
	}

	start->cell.setFillColor(sf::Color::Green);
	finish->cell.setFillColor(sf::Color::Red);
	for (auto i = grid.nodes.begin(); i != grid.nodes.end(); ++i)
	{
		if (i->nodeIndex != start->nodeIndex && i->nodeIndex != finish->nodeIndex)
			i->value == 0 ? i->cell.setFillColor(sf::Color::White) : i->cell.setFillColor(sf::Color::Magenta);
	}

	bool middleMouseButtonPressed = false;
	sf::Event event;
	//Game loop
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			sf::Vector2i mousePos = sf::Mouse::getPosition(window);
			sf::Vector2f mousePosf(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

			int i = -1;
			for (auto &node : grid.nodes)
				if (node.cell.getGlobalBounds().contains(mousePosf))
					i = node.nodeIndex;

			// end the program
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			//Track mouse movement
			if (event.type == sf::Event::MouseMoved)
			{
				if (startButton.getRect().getGlobalBounds().contains(mousePosf))
				{
					startButton.getRect().setFillColor(sf::Color(150, 150, 150, 150));
				}
				else
				{
					startButton.getRect().setFillColor(sf::Color(150, 150, 150, 255));
				}
				if (resetButton.getRect().getGlobalBounds().contains(mousePosf))
				{
					resetButton.getRect().setFillColor(sf::Color(150, 150, 150, 150));
				}
				else
				{
					resetButton.getRect().setFillColor(sf::Color(150, 150, 150, 255));
				}
				
				// Mark the unwalkable nodes
				if (middleMouseButtonPressed && i != -1
					&& grid.nodes.at(i).nodeIndex != start->nodeIndex
					&& grid.nodes.at(i).nodeIndex != finish->nodeIndex)
				{
					if (grid.nodes.at(i).nodeValueChanged == false)
					{
						if (grid.nodes.at(i).value == 0)
						{
							grid.nodes.at(i).nodeValueChanged = true;
							grid.nodes.at(i).value = 1;
							grid.nodes.at(i).cell.setFillColor(sf::Color::Magenta);
						}
						else
						{
							grid.nodes.at(i).nodeValueChanged = true;
							grid.nodes.at(i).value = 0;
							grid.nodes.at(i).cell.setFillColor(sf::Color::White);
						}
					}
				}
			}
			if (event.type == sf::Event::MouseButtonPressed)
			{
				// Right mouse button click
				if (event.mouseButton.button == sf::Mouse::Right && i != -1
					&& grid.nodes.at(i).value == 0 && grid.nodes.at(i).nodeIndex != start->nodeIndex)
				{
					// Mark the finish node
					if (finish == nullptr) finish = &grid.nodes.at(i);
					finish->cell.setFillColor(sf::Color::White);
					finish = &grid.nodes.at(i);
					finish->cell.setFillColor(sf::Color::Red);
				}

				// Middle button mouse click
				if (event.mouseButton.button == sf::Mouse::Middle)
				{
					middleMouseButtonPressed = true;
				}

				// Left mouse button click
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					// Mark the start node
					if (i != -1 && grid.nodes.at(i).value == 0
						&& grid.nodes.at(i).nodeIndex != finish->nodeIndex)
					{
						if (start == nullptr) start = &grid.nodes.at(i);
						start->cell.setFillColor(sf::Color::White);
						start = &grid.nodes.at(i);
						start->cell.setFillColor(sf::Color::Green);
					}

					// START Button
					if (startButton.getRect().getGlobalBounds().contains(mousePosf))
					{
						if (PathfindingForm::algorithmChoice == PathfindingForm::Alg_Choice::Random)
							Random_Search(grid, start, finish);
						else if (PathfindingForm::algorithmChoice == PathfindingForm::Alg_Choice::Astar)
							A_Star(grid, start, finish, PathfindingForm::heuristicChoice);
						else if (PathfindingForm::algorithmChoice == PathfindingForm::Alg_Choice::GreedyBFS)
							Greedy_Best_FS(grid, start, finish);
						else if (PathfindingForm::algorithmChoice == PathfindingForm::Alg_Choice::Dijkstra)
							Dijkstra_Search(grid, start, finish);
					}

					// RESET Button
					if (resetButton.getRect().getGlobalBounds().contains(mousePosf))
					{
						for (auto &node : grid.nodes)
						{
							node.value = 0;
							node.Clear();
							node.cell.setFillColor(sf::Color::White);
						}
						/* 
						*  Regarding reading from a file:
						*  Must do this otherwise grid has the old
						*  values loaded from the file 
						*/
						grid = Grid(vector<vector<int>>(PathfindingForm::columns, vector<int>(PathfindingForm::rows, 0)));

						start = &grid.nodes.at(0);
						finish = &grid.nodes.at(grid.nodes.size() - 1);
						start->cell.setFillColor(sf::Color::Green);
						finish->cell.setFillColor(sf::Color::Red);
					}
				}
			}
			if (event.type == sf::Event::MouseButtonReleased)
			{
				if (event.mouseButton.button == sf::Mouse::Middle)
				{
					if (i != -1 && grid.nodes.at(i).nodeValueChanged == false
						&& grid.nodes.at(i).nodeIndex != start->nodeIndex
						&& grid.nodes.at(i).nodeIndex != finish->nodeIndex)
					{
						if (grid.nodes.at(i).value == 0)
						{
							grid.nodes.at(i).nodeValueChanged = true;
							grid.nodes.at(i).value = 1;
							grid.nodes.at(i).cell.setFillColor(sf::Color::Magenta);
						}
						else
						{
							grid.nodes.at(i).nodeValueChanged = true;
							grid.nodes.at(i).value = 0;
							grid.nodes.at(i).cell.setFillColor(sf::Color::White);
						}
					}

					middleMouseButtonPressed = false;
					for (auto &node : grid.nodes)
						if (node.nodeValueChanged == true)
							node.nodeValueChanged = false;
				}
			}
		}

		window.clear(sf::Color::Black);
		startButton.draw(window);
		resetButton.draw(window);
		for (size_t i = 0; i < grid.nodes.size(); ++i)
			window.draw(grid.nodes.at(i).cell);
		window.display();
	}
}