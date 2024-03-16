# Urban-Managment-System
The project involves adding buildings to the database and assigning residents, employees and managers to these buillding. At the end, it has to conduct a statistical analysis of these data.



Objective:
Given commands from the keyboard for adding/removing buildings or individuals with different statuses in those buildings, generate statistics on certain attributes related to specific types of individuals or the type of settlement, as described in the Output Data section. The goal is to create a settlement, which can be a village, town, or capital, depending on the number and type of buildings added to that settlement from the keyboard input.

Output data:
The output will consist of a statistics regarding the settlement created using these buildings as follows:

Type: the type of settlement. This type can be "Village", "Town", or "Capital". To determine the type of settlement, the following conditions must be met:
  Capital: CityHall >=3, Hospital >= 2, PoliceStation >= 3, House >= 8, Block >= 4
  City: CityHall >=2, Hospital >= 1, PoliceStation >= 2, House >= 4, Block >= 1
  Village: Anything else besides the above conditions
Number of patients in hospitals: the total number of patients in all hospitals
Average salary for doctors: the average salary of all doctors in all hospitals
Average salary for cops: the average salary of all police officers in all police stations
Average salary for mayors: the average salary of all mayors in all city halls
Average salary for city hall employees: the average salary of all employees in all city halls
Average age of busted in police stations: the average age of all persons arrested in all police stations
The following lines should be in the format:
Number of people in House house_name: the number of people in that house, including the owner if exists
Number of people in Block block_name: the number of people in that block, including the administrator if exists
The above lines will be arranged in the order in which houses and blocks were given from the keyboard.
Administrators of house and block: the names of persons who are both block administrators and house owners. If no person exists, "Nobody" will be displayed.

