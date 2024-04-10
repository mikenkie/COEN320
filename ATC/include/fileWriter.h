/*
 * fileWriter.h
 *
 *  Created on: Apr 10, 2024
 *      Author: matth
 */

#ifndef FILEWRITER_H_
#define FILEWRITER_H_

class fileWriter {
public:
	fileWriter();
	virtual ~fileWriter();

	void writeLow();
	void writeMed();
	void writeHigh();
	void writeOver();
};

#endif /* FILEWRITER_H_ */
