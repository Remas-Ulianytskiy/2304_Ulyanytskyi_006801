#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Doctor {
private:
    string specialization;

public:
    Doctor(string specialization) : specialization(specialization) {}

    string get_specialization() const { return specialization; }

    bool visit()
    {
        cout << "Visited " << specialization << " doctor." << endl;
        return true;
    }
};

class Visitor {
private:
    string profession;
    vector<string> visited_offices;

public:
    Visitor(string profession) : profession(profession) {}

    string get_profession() const { return profession; }

    bool visit_doctor(Doctor& doctor)
    {
        bool success = doctor.visit();
        visited_offices.push_back(doctor.get_specialization());
        return success;
    }

    bool check_visit(string specialization)
    {
        return find(visited_offices.begin(), visited_offices.end(), specialization) != visited_offices.end();
    }

    bool check_all_visits()
    {
        vector<string> offices = { "Dermatologist", "ENT Specialist", "Radiologist", "Dentist" };
        return offices.size() == visited_offices.size() &&
            equal(offices.begin(), offices.end(), visited_offices.begin());
    }
};

int main() {
    Doctor dermatologist("Dermatologist");
    Doctor ent_specialist("ENT Specialist");
    Doctor radiologist("Radiologist");
    Doctor dentist("Dentist");

    Visitor doctor("Doctor");
    Visitor teacher("Teacher");
    Visitor security_guard("Security Guard");

    doctor.visit_doctor(dermatologist);
    doctor.visit_doctor(ent_specialist);
    doctor.visit_doctor(radiologist);
    doctor.visit_doctor(dentist);

    teacher.visit_doctor(dermatologist);
    teacher.visit_doctor(dentist);

    security_guard.visit_doctor(ent_specialist);
    security_guard.visit_doctor(radiologist);

    cout << "Doctor visits successful? " << (doctor.check_all_visits() ? "Yes" : "No") << endl;
    cout << "Teacher visits successful? " << (teacher.check_all_visits() ? "Yes" : "No") << endl;
    cout << "Security Guard visits successful? " << (security_guard.check_all_visits() ? "Yes" : "No") << endl;

    return 0;
}
