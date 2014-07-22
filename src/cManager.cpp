/*
 * cManager.cpp
 *
 *  Created on: 19 lip 2014
 *      Author: abby
 */

#include "cManager.h"

cManager::cManager() :
		dataFile("data.txt") {
	cout << "--FileControl--" << endl; // prints tmp
	cout << DBG << dataFile << endl;
}

cManager::cManager(cFile toAdd) :
		dataFile("data.txt") {
	bool ok = add(toAdd);
}

void cManager::displayMap() {
	cout << "---DISPLAYING MAP!!---" << endl;
	map<string, cFile>::iterator it = this->hashFiles.begin();
	for (it = this->hashFiles.begin(); it != this->hashFiles.end(); ++it)
		cout << "- " << it->first << " => " << it->second.getName() << endl;

//		cout << "   " << it->first << " => " << it->second.toString() << endl;
	cout << "------END MAP---------" << endl;
}

string cManager::getHash(string &filename) {
	CryptoPP::SHA512 sha512;
	string hash = "";
	fstream file;
	file.open(filename.c_str(), ios::in);

	CryptoPP::FileSource(file, true, new CryptoPP::HashFilter(sha512, new CryptoPP::HexEncoder(new CryptoPP::StringSink(hash))));
	cout << DBG << filename << "\t" << hash << endl;
	return hash;
}

string cManager::getHash(cFile file) {
	string filename = file.getName();
	return getHash(filename);
}
map<string, cFile> cManager::getMap() {
	return hashFiles;
}

bool cManager::addToMap(string &hash, cFile file) {
	map<string, cFile>::iterator it = this->hashFiles.find(hash);
	// if this file is arleady in map
	if (it != hashFiles.end()) {
		cout << DBG << "File is arleady in map" << endl;
		return false;
	}

	pair<map<string, cFile>::iterator, bool> ret;
	ret = this->hashFiles.insert(pair<string, cFile>(hash, file));
	return true;
}

bool cManager::add(cFile toAdd) {
	cout << DBG << "File to add:  " << toAdd.getName() << endl;
	string hash = getHash(toAdd);
	if (!addToMap(hash, toAdd)) {
		cout << DBG << "Can't add to map " << toAdd.getName() << endl;
		return false;
	}
	displayMap();
	return true;
}

cManager::~cManager() {
	// TODO Auto-generated destructor stub
}

bool cManager::loadFromFileToMap() {
	return false;
}

bool cManager::saveMapToFile() {
	return false;
}

