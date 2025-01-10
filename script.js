// Function to load student data from localStorage (or mock JSON data)
function loadStudents() {
    const studentsList = JSON.parse(localStorage.getItem("students")) || [];
    const studentsDiv = document.getElementById("studentsList");
    studentsDiv.innerHTML = ''; // Clear the current list

    studentsList.forEach(student => {
        const studentDiv = document.createElement('div');
        studentDiv.innerHTML = `
            <strong>Roll No:</strong> ${student.rollNo} <br>
            <strong>Name:</strong> ${student.name} <br>
            <strong>Marks:</strong> ${student.marks} <br>
            <strong>Grade:</strong> ${student.grade}
        `;
        studentsDiv.appendChild(studentDiv);
    });
}

// Function to search for a student by Roll No
function searchStudent() {
    const rollNo = document.getElementById("searchRollNo").value;
    const studentsList = JSON.parse(localStorage.getItem("students")) || [];
    const searchResultDiv = document.getElementById("searchResult");

    const foundStudent = studentsList.find(student => student.rollNo === parseInt(rollNo));

    if (foundStudent) {
        searchResultDiv.innerHTML = `
            <strong>Roll No:</strong> ${foundStudent.rollNo} <br>
            <strong>Name:</strong> ${foundStudent.name} <br>
            <strong>Marks:</strong> ${foundStudent.marks} <br>
            <strong>Grade:</strong> ${foundStudent.grade}
        `;
    } else {
        searchResultDiv.innerHTML = `No student found with Roll No: ${rollNo}`;
    }
}

// Function to add a new student
document.getElementById("addStudentForm").addEventListener("submit", function (event) {
    event.preventDefault();  // Prevent form submission

    const rollNo = document.getElementById("rollNo").value;
    const name = document.getElementById("name").value;
    const marks = document.getElementById("marks").value;
    let grade = '';

    if (marks >= 90) grade = 'A';
    else if (marks >= 75) grade = 'B';
    else if (marks >= 50) grade = 'C';
    else grade = 'F';

    const newStudent = { rollNo: parseInt(rollNo), name, marks: parseInt(marks), grade };

    // Get the existing students data from localStorage and add the new student
    const studentsList = JSON.parse(localStorage.getItem("students")) || [];
    studentsList.push(newStudent);

    // Save the updated list back to localStorage
    localStorage.setItem("students", JSON.stringify(studentsList));

    alert("Student added successfully!");
    loadStudents();  // Reload the student list after adding
});

// Load students when the page is loaded
document.getElementById("loadStudents").addEventListener("click", loadStudents);

// Initially load students
loadStudents();

// Toggle the visibility of the student list
function toggleStudentList() {
    const studentsListDiv = document.getElementById("studentsList");
    const toggleButton = document.getElementById("toggleStudentList");

    studentsListDiv.classList.toggle("hidden");

    if (studentsListDiv.classList.contains("hidden")) {
        toggleButton.innerHTML = "Open";  // Change text to 'Open' when closed
    } else {
        toggleButton.innerHTML = "Close";  // Change text back to 'Close' when open
    }
}
