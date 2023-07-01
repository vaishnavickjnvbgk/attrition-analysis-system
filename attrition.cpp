#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <vector>
#include <iomanip>


struct Employee {
    std::string name;
    std::string role;
    std::time_t startDate;
    std::time_t quitDate;
};

// Function to calculate the percentage
double calculatePercentage(int count, int total) {
    if (total == 0)
        return 0.0;
    else
        return static_cast<double>(count) / total * 100.0;
}

Employee parseEmployeeData(const std::string& line) {
    std::istringstream iss(line);
    std::string name, role, startDateString, quitDateString;
    iss >> name >> role >> startDateString >> quitDateString;

    std::tm startDate{};
    std::istringstream startDateStream(startDateString);
    startDateStream >> std::get_time(&startDate, "%Y-%m-%d");
    std::time_t startTime = std::mktime(&startDate);

    std::tm quitDate{};
    std::istringstream quitDateStream(quitDateString);
    quitDateStream >> std::get_time(&quitDate, "%Y-%m-%d");
    std::time_t quitTime = std::mktime(&quitDate);

    return {name, role, startTime, quitTime};
}

int main() {
    std::ifstream inputFile("employee_data.txt"); // Assuming the data is stored in "employee_data.txt"
    if (!inputFile) {
        std::cerr << "Failed to open the input file." << std::endl;
        return 1;
    }

    std::vector<Employee> employees;
    std::string line;
    while (std::getline(inputFile, line)) {
        employees.push_back(parseEmployeeData(line));
    }
    inputFile.close();

    // Prompt the user for start and end dates
    std::string startDateInput, endDateInput;
    std::cout << "Enter the start date (YYYY-MM-DD): ";
    std::cin >> startDateInput;
    std::cout << "Enter the end date (YYYY-MM-DD): ";
    std::cin >> endDateInput;

    std::tm startDate{};
    std::istringstream startDateStream(startDateInput);
    startDateStream >> std::get_time(&startDate, "%Y-%m-%d");
    std::time_t startTime = std::mktime(&startDate);

    std::tm endDate{};
    std::istringstream endDateStream(endDateInput);
    endDateStream >> std::get_time(&endDate, "%Y-%m-%d");
    std::time_t endTime = std::mktime(&endDate);

    int totalSoftwareEngineers = 0;
    int quitSoftwareEngineers = 0;
    int quitBefore2YearsSoftwareEngineers = 0;
    int quitAfter2YearsSoftwareEngineers = 0;

    int totalSeniorSoftwareEngineers = 0;
    int quitSeniorSoftwareEngineers = 0;
    int quitBefore2YearsSeniorSoftwareEngineers = 0;
    int quitAfter2YearsSeniorSoftwareEngineers = 0;

    int totalTechLeads = 0;
    int quitTechLeads = 0;
    int quitBefore2YearsTechLeads = 0;
    int quitAfter2YearsTechLeads = 0;

    // Iterate over the employees and perform the analysis
    for (const Employee& employee : employees) {
        if (employee.quitDate >= startTime && employee.quitDate <= endTime) {
            if (employee.role == "Software Engineer") {
                totalSoftwareEngineers++;
                quitSoftwareEngineers++;
                if (employee.quitDate >= employee.startDate + (2 * 365 * 24 * 60 * 60))
                    quitAfter2YearsSoftwareEngineers++;
                else
                    quitBefore2YearsSoftwareEngineers++;
            }
            else if (employee.role == "Senior Software Engineer") {
                totalSeniorSoftwareEngineers++;
                quitSeniorSoftwareEngineers++;
                if (employee.quitDate >= employee.startDate + (2 * 365 * 24 * 60 * 60))
                    quitAfter2YearsSeniorSoftwareEngineers++;
                else
                    quitBefore2YearsSeniorSoftwareEngineers++;
            }
            else if (employee.role == "Tech Lead") {
                totalTechLeads++;
                quitTechLeads++;
                if (employee.quitDate >= employee.startDate + (2 * 365 * 24 * 60 * 60))
                    quitAfter2YearsTechLeads++;
                else
                    quitBefore2YearsTechLeads++;
            }
        }
    }

    // Calculate the percentages
    double quitPercentageSoftwareEngineers = calculatePercentage(quitSoftwareEngineers, totalSoftwareEngineers);
    double quitPercentageSeniorSoftwareEngineers = calculatePercentage(quitSeniorSoftwareEngineers, totalSeniorSoftwareEngineers);
    double quitPercentageTechLeads = calculatePercentage(quitTechLeads, totalTechLeads);

    double quitBefore2YearsPercentageSoftwareEngineers = calculatePercentage(quitBefore2YearsSoftwareEngineers, quitSoftwareEngineers);
    double quitBefore2YearsPercentageSeniorSoftwareEngineers = calculatePercentage(quitBefore2YearsSeniorSoftwareEngineers, quitSeniorSoftwareEngineers);
    double quitBefore2YearsPercentageTechLeads = calculatePercentage(quitBefore2YearsTechLeads, quitTechLeads);

    double quitAfter2YearsPercentageSoftwareEngineers = calculatePercentage(quitAfter2YearsSoftwareEngineers, quitSoftwareEngineers);
    double quitAfter2YearsPercentageSeniorSoftwareEngineers = calculatePercentage(quitAfter2YearsSeniorSoftwareEngineers, quitSeniorSoftwareEngineers);
    double quitAfter2YearsPercentageTechLeads = calculatePercentage(quitAfter2YearsTechLeads, quitTechLeads);

    // Output the results
    std::cout << "Quit percentages by role from " << startDateInput << " to " << endDateInput << ":" << std::endl;
    std::cout << "==============================================" << std::endl;
    std::cout << "Software Engineer: " << quitPercentageSoftwareEngineers << "%" << std::endl;
    std::cout << "Senior Software Engineer: " << quitPercentageSeniorSoftwareEngineers << "%" << std::endl;
    std::cout << "Tech Lead: " << quitPercentageTechLeads << "%" << std::endl;
    std::cout << std::endl;

    std::cout << "Quit percentages before 2 years by role from " << startDateInput << " to " << endDateInput << ":" << std::endl;
    std::cout << "==============================================" << std::endl;
    std::cout << "Software Engineer: " << quitBefore2YearsPercentageSoftwareEngineers << "%" << std::endl;
    std::cout << "Senior Software Engineer: " << quitBefore2YearsPercentageSeniorSoftwareEngineers << "%" << std::endl;
    std::cout << "Tech Lead: " << quitBefore2YearsPercentageTechLeads << "%" << std::endl;
    std::cout << std::endl;

    std::cout << "Quit percentages after 2 years by role from " << startDateInput << " to " << endDateInput << ":" << std::endl;
    std::cout << "==============================================" << std::endl;
    std::cout << "Software Engineer: " << quitAfter2YearsPercentageSoftwareEngineers << "%" << std::endl;
    std::cout << "Senior Software Engineer: " << quitAfter2YearsPercentageSeniorSoftwareEngineers << "%" << std::endl;
    std::cout << "Tech Lead: " << quitAfter2YearsPercentageTechLeads << "%" << std::endl;

    return 0;
}
