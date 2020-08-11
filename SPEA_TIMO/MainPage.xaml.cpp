//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

#include <numeric>

#include "Spea.hpp"

using namespace SPEA_TIMO;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

// The Blank Page item template is documented at https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

MainPage::MainPage()
{
	InitializeComponent();
}


void MainPage::ConsoleOutput_TextChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::TextChangedEventArgs^ e)
{

}


void MainPage::Button_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	this->ConsoleOutput->Text += "\nSiemanko\n";
	Spea::FitnessFunction f {
		[](const Spea::Genom& genom) -> double
		{
			return std::accumulate(std::begin(genom), std::end(genom), 0);
		},
		[](const Spea::Genom& genom) -> double
		{
			return -std::accumulate(std::begin(genom), std::end(genom), 0) - 30;
		}};
	Spea spea(f);
	spea.run();
	auto p = spea.getAchive();
	for (const auto& genom : p)
	{
		for (const auto& gen : genom)
		{
			this->ConsoleOutput->Text += gen + ", ";
		}
		this->ConsoleOutput->Text += "\n";
	}
}


void MainPage::ComboBox_SelectionChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs^ e)
{

}
