///////////////////////////////////
// Author: Konstantin Lampalzer  //
// Date: 26.09.2018              //
// Project: PThreads             //
///////////////////////////////////

#pragma once

class Display;
class Customer
{
private:
  Display *display;
  int ticketNumber;

  void respondToDisplay();
  void waitForCorrectTicketNumber();

public:
  Customer(int _ticketNumber, Display *_display);
  ~Customer();
  void waitForFreeCounter();

  // Getter + Setter
  const int getTicketNumber();
};
