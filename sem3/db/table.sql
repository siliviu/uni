USE LanguageCentre

DROP TABLE IF EXISTS Teacher_Knowledge
DROP TABLE IF EXISTS Pupil_Knowledge
DROP TABLE IF EXISTS Results
DROP TABLE IF EXISTS Evaluations
DROP TABLE IF EXISTS Contracts
DROP TABLE IF EXISTS Teachers
DROP TABLE IF EXISTS Enrollments
DROP TABLE IF EXISTS Classes
DROP TABLE IF EXISTS Courses
DROP TABLE IF EXISTS Languages
DROP TABLE IF EXISTS Pupils

CREATE TABLE Pupils(
pupil_id		INT				PRIMARY KEY		IDENTITY,
name			VARCHAR(50)		NOT NULL,
date_birth		DATE			NOT NULL,
description		VARCHAR(100)
);

CREATE TABLE Languages(
language_id		INT				PRIMARY KEY		IDENTITY,
name			VARCHAR(25)		NOT NULL
);

CREATE TABLE Courses(
course_id		INT				PRIMARY KEY		IDENTITY,
name			VARCHAR(50)		NOT NULL		UNIQUE,
description		VARCHAR(100),
length			INT				NOT NULL,
difficulty		VARCHAR(20)		NOT NULL,
language_id		INT				FOREIGN KEY		REFERENCES Languages(language_id) ON DELETE CASCADE
);

CREATE TABLE Classes(
class_id		INT				PRIMARY KEY		IDENTITY,
name			VARCHAR(100)	NOT NULL		UNIQUE,
year			INT				NOT NULL,
course_id		INT				FOREIGN KEY		REFERENCES Courses(course_id) ON DELETE CASCADE
);

CREATE TABLE Enrollments(
date			DATE			NOT NULL,
cost			INT				NOT NULL,
finished		BIT				DEFAULT 0,
pupil_id		INT				FOREIGN KEY		REFERENCES Pupils(pupil_id) ON DELETE CASCADE,
class_id		INT				FOREIGN KEY		REFERENCES Classes(class_id) ON DELETE CASCADE,
CONSTRAINT		enrollment_id	PRIMARY KEY(pupil_id, class_id)
);

CREATE TABLE Teachers(
teacher_id		INT				PRIMARY KEY		IDENTITY,
studies			VARCHAR(100)	NOT NULL,
name			VARCHAR(50)		NOT NULL,
description		VARCHAR(100)
);

CREATE TABLE Contracts(
date			DATE			NOT NULL,
salary			INT				NOT NULL,
teacher_id		INT				FOREIGN KEY		REFERENCES Teachers(teacher_id) ON DELETE CASCADE,
class_id		INT				FOREIGN KEY		REFERENCES Classes(class_Id) ON DELETE CASCADE
CONSTRAINT		contract_id		PRIMARY KEY(teacher_id,class_id)
);

CREATE TABLE Evaluations (
evaluation_id	INT				PRIMARY KEY		IDENTITY,
time			TIME			NOT NULL,
max_score		INT				NOT NULL		CHECK(max_score > 0),
course_id		INT				FOREIGN KEY		REFERENCES Courses(course_id) ON DELETE CASCADE
);

CREATE TABLE Results (
score			INT				NOT NULL		CHECK(score >= 0),
pupil_id		INT				FOREIGN KEY		REFERENCES Pupils(pupil_id) ON DELETE CASCADE,
evaluation_id	INT				FOREIGN KEY		REFERENCES Evaluations(evaluation_id)ON DELETE CASCADE,
CONSTRAINT		result_id		PRIMARY KEY(pupil_id, evaluation_id)
);

CREATE TABLE Pupil_Knowledge (
level			VARCHAR(20)		NOT NULL,
date_learnt		DATE			NOT NULL,
language_id		INT				FOREIGN KEY		REFERENCES Languages(language_id) ON DELETE CASCADE,
pupil_id		INT				FOREIGN KEY		REFERENCES Pupils(pupil_id) ON DELETE CASCADE
CONSTRAINT		pknowledge_id	PRIMARY KEY(pupil_id, language_id)
);

CREATE TABLE Teacher_Knowledge (
level			VARCHAR(16)		NOT NULL,
date_teaching	DATE			NOT NULL,
language_id		INT				FOREIGN KEY		REFERENCES Languages(language_id) ON DELETE CASCADE,
teacher_id		INT				FOREIGN KEY		REFERENCES Teachers(teacher_id) ON DELETE CASCADE,
CONSTRAINT		tknowledge_id	PRIMARY KEY(teacher_id, language_id)
);