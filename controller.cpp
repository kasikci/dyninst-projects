#include "PCProcess.h"
#include "Event.h"
#include <iostream>
#include <string>

using namespace Dyninst;
using namespace ProcControlAPI;
using namespace std;

Process::cb_ret_t on_thread_create(Event::const_ptr ev)
{
  // Callback when the target process creates a thread.
  EventNewThread::const_ptr new_thrd_ev = ev->getEventNewThread();
  Thread::const_ptr new_thrd = new_thrd_ev->getNewThread();
  cout << "Got a new thread with LWP " << new_thrd->getLWP() << endl;

  return Process::cbDefault;
}
int main(int argc, char *argv[]) {
  vector<string> args;
  
  // Create a new target process
  string exec = argv[1];
  for (unsigned i=1; i<argc; i++)
    args.push_back(std::string(argv[i]));

  Process::ptr proc = Process::createProcess(exec, args);
  assert (proc != NULL && "Proc cannot be NULL!");
  // Tell ProcControlAPI about our callback function
  Process::registerEventCallback(EventType::ThreadCreate, on_thread_create);

  // Run the process and wait for it to terminate.  
  proc->continueProc();

  while (!proc->isTerminated())
    Process::handleEvents(true);
  return 0;
}
