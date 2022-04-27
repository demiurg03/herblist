CREATE TABLE "Herb" (
	"ID"	INTEGER NOT NULL,
	"Name"	TEXT,
  	"Content" INTEGER,
  	"TrLang" INTEGER,
	PRIMARY KEY("ID" AUTOINCREMENT)
);

CREATE TABLE "Content" (
	"ID"	INTEGER NOT NULL,
	"ContentId"	INTEGER,
  	"Lang" TEXT,
  	"Path" TEXT,
	PRIMARY KEY("ID" AUTOINCREMENT)
);


CREATE TABLE "TrLang" (
	"ID"	INTEGER NOT NULL,
	"TrLangId"	INTEGER,
  	"Lang" TEXT,
  	"Name" TEXT,
	PRIMARY KEY("ID" AUTOINCREMENT)
);
