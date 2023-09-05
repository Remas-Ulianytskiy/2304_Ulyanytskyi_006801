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

    bool visit(string& profession)
    {
        cout << profession <<" visited " << specialization << " doctor." << endl;
        return true;
    }
};

class Visitor {
private:
    string profession;    
    vector<string> need_to_visit;
    vector<string> visited_offices;

public:
    Visitor(string profession, vector<string> need_to_visit) 
        : profession(profession), need_to_visit(need_to_visit) 
    {}

    string get_profession() const { return profession; }

    bool visit_doctor(Doctor& doctor)
    {
        bool success = doctor.visit(profession);
        visited_offices.push_back(doctor.get_specialization());
        return success;
    }

    bool check_visit(string specialization)
    {
        return find(visited_offices.begin(), visited_offices.end(), specialization) != visited_offices.end();
    }

    bool check_all_visits()
    {
        for (const string& doctor_to_visit : need_to_visit)
            if (find(visited_offices.begin(), visited_offices.end(), doctor_to_visit) == visited_offices.end())
                return false;
        return true;
    }
};

int main() {
    const vector<string> DOCTORS_SPEC 
    {
        "Dermatologist", "ENT Specialist",
        "Radiologist", "Dentist", "Fluorography"
    };

    const vector<string> doctor_need_to_visit { DOCTORS_SPEC[0], DOCTORS_SPEC[3] };
    const vector<string> teacher_need_to_visit { DOCTORS_SPEC[1], DOCTORS_SPEC[3] };
    const vector<string> security_guard_need_to_visit { DOCTORS_SPEC[2], DOCTORS_SPEC[4] };

    Doctor dermatologist("Dermatologist");
    Doctor ent_specialist("ENT Specialist");
    Doctor radiologist("Radiologist");
    Doctor dentist("Dentist");
    Doctor fluorography("Fluorography");

    Visitor doctor("Doctor", doctor_need_to_visit);
    Visitor teacher("Teacher", teacher_need_to_visit);
    Visitor security_guard("Security Guard", security_guard_need_to_visit);

    cout << "Doctor need to visit: " << doctor_need_to_visit[0] << ' ' << doctor_need_to_visit[1];
    cout << "\nTeacher need to visit: " << teacher_need_to_visit[0] << ' ' << teacher_need_to_visit[1];
    cout << "\nSecurity Guard need to visit: " << security_guard_need_to_visit[0] << ' ' << security_guard_need_to_visit[1];
    cout << endl << endl;

    doctor.visit_doctor(dermatologist);
    doctor.visit_doctor(ent_specialist);
    doctor.visit_doctor(radiologist);
    doctor.visit_doctor(dentist);

    cout << endl;

    teacher.visit_doctor(dermatologist);
    teacher.visit_doctor(ent_specialist);
    teacher.visit_doctor(dentist);

    cout << endl;

    security_guard.visit_doctor(ent_specialist);
    security_guard.visit_doctor(radiologist);

    cout << endl;

    cout << "Doctor visits successful? " << (doctor.check_all_visits() ? "Yes" : "No") << endl;
    cout << "Teacher visits successful? " << (teacher.check_all_visits() ? "Yes" : "No") << endl;
    cout << "Security Guard visits successful? " << (security_guard.check_all_visits() ? "Yes" : "No") << endl;

    return 0;
}
