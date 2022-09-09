#include <chrono>
#include <iomanip>
#include <iostream>
#include <string>
#include <unistd.h>



using string = std::string;

// Function headers go here
void set_phase_duration(int &phase_duration, string desired_phase);
bool input_checker(string user_input);
void execute_phase(string phase_name, int phase_duration);


void set_phase_duration(int &phase_duration, string desired_phase) {
  // Check to make sure that the duration is valid (integer > 0)
  string input_gathered;
  std::cout << "How long do you wish to " << desired_phase
            << " for, in minutes?" << std::endl;
  std::cin >> input_gathered;

  bool input_valid = input_checker(input_gathered);

  // So long as the duration isn't valid, prompt user to enter a valid one
  while (!input_valid) {
    std::cout << "Invalid input. Please enter an int duration > 0" << std::endl;
    std::cin >> input_gathered;
    input_valid = input_checker(input_gathered);
  }

  phase_duration = stoi(input_gathered);
  // Let the user know the phase setting was successful through output
  std::cout << desired_phase << " duration set to " << phase_duration << " mins"
            << std::endl;
}

bool input_checker(string user_input) {
  // If the input is a char, then it isn't valid
  for (unsigned int i = 0; i < user_input.length(); i++) {
    if (isdigit(user_input[i]) == false)
      return false;
  }
  // Additionally, if the user enters 0 for duration, input invalid
  if (stoi(user_input) == 0) {
    return false;
  }
  return true;
}

void execute_phase(string phase_name, int phase_duration) {
  // sleep works in seconds, so convert the phase durations and output phase
  // length
  double phase_seconds = phase_duration * 60.0;
  std::cout << "Beginning " << phase_name << " phase: " << phase_duration
            << " minute(s)" << std::endl;
  while (phase_seconds > 0.0) {
    // Sleep the program for 30 sec. then dec duration to avoid inf. loop
    sleep(30);
    phase_seconds -= 30;
    // Keep user apprised of the time remaining in phase
    std::cout << "Remaining " << phase_name
              << " time: " << (phase_seconds / 60.0) << " minutes "
              << std::endl;
  }
  std::cout << phase_name << " phase concluded. \n" << std::endl;
}

int main() {
  std::cout << "Welcome to Pomotimer!\n" << std::endl;
  int work_duration = 0;
  int rest_duration = 0;

  // Get the duration of both phases
  set_phase_duration(work_duration, "Work");
  std::cout << std::endl;
  set_phase_duration(rest_duration, "Rest");
  std::cout << std::endl;

  // Set a boolean to be set to false when the work/rest phase elapses
  bool cycle_timer = true;
  while (cycle_timer) {

    // give the timer an in-terminal header for housekeeping
    std::cout << "Beginning timer cycle now" << std::endl;
 
    std::cout << std::setfill('-') << std::setw(50);
    std::cout << "\n";

    // Execute the work phase
    execute_phase("Work", work_duration);


    // Stops execution of the program until user enters something
    std::cout << "Press any alphanumeric character then enter to continue: ";
    string continue_check = " ";
    std::cin >> continue_check;

    // Execute the rest phase
    execute_phase("Rest", rest_duration);

    // Timer loop ends w/ rest phase, ask user if they want to cycle again
    std::cout << "Timer loop concluded \n"
              << "Restart timer loop? (Y/N)" << std::endl;
    
    char restart_loop;
    bool input_valid = false;
    while (!input_valid) {
      std::cin >> restart_loop;
      restart_loop = toupper(restart_loop);
      switch (restart_loop) {
      case 'Y':
        system("clear");
        input_valid = true;
        break;
      case 'N':
        std::cout << "No longer cycling timer; "
                  << "Thank you for using Pomotimer!" << std::endl;
        cycle_timer = false;
        input_valid = true;
        break;
      default:
        std::cout << "Invalid input... Restart timer (Y/N)? ";
        break;
      }
    }
  }
  return 0;
}
