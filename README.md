# Nurses Work Schedule

## Assumptions

- All workers are unique
- Worker after one shift has 2 shifts of rest
- Each worker have 1 weekend off in a month

## Work Day

- 2 shifts in hours:
  - 7:00 - 19:00
  - 19:00 - 7:00
- Min 2 workers on shift
- Possibility of change amount of workers in each day 
- 14 shifts * 5 = 70 shifts in month

## Functions

- Input/Output
    - mode1 (reporting)
    - mode2 (holidays)
    - mode3 (workers)
- Reporting
    - Generate report
    - Show report for worker
    - Show report for managment
- Workers
    - List of workers
    - Add worker
    - Delete worker

## 3 files in CSV format

1. Worker 
    - Format: `FirstName; LastName; Id`
2. Schedule
    - Format: `Day; Shift; FirstName; LastName; Overtime`
3. Holidays
    - Format: `FirstName; LastName; Day; Month; Year; ForAllDay; Shift`

## Classes

- CSVFileReader:
    - readFile(filename) `return matrix of vektor with lines and columns`
- IO (interface)
    - readcommand
- mainIO (IO)
    - switch mode
    - execute procedure
- Procedure (interface)
    - runprocedure
- generatePlan (Procedure)
- generatePlanForNurses (Procedure)
- generatePlanForAll (Procedure)
- help (Procedure)
- DateToPart
    - convertDateToString() `gets "20.12.2023" return indexes`
- Nurse
    - m_firstname
    - m_surname
    - id
    - (vector int) holidays `0 - 69`
    - dateToPart* converter
    - addHolidays (int part)
- Shift
    - day
    - month
    - year
    - part `1(7:00-19:00) 2(19:00-7:00)`
    - (vector *Nurses) nursesAtThisDay

## Schedule of Work
- Michał Borzuchowski
  1. Editing the ScheduleCreartor class to check the breaks between shifts and verify that weekend holidays are inserted correctly (1 - 2 work days)
  2. Replacing missing hours with overtime for employees, i.e. changing the ScheduleCreator class (1 day of work)
  3. Do another .exe file for reading for employee
- Mateusz Smolarek
  1. Do unit test in Gtest for ScheduleCreator which check assumptions of program (1 day of work)
  2. Do a code coverage for testes (1 - 2 work days)
  3. Change an apperince of testes form .exe file to subdirectories (1 day of work)
- Meetings
  - 2024-01-15 (Metting start on 20 o'clock and ends 30 minutes later) :white_check_mark:
  - 2024-01-18 (Metting start on 19 o'clock and ends 45 minutes later) :white_check_mark:
