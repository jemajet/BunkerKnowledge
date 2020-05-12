Bunker Knowledge is a project that uses the PSoC 5 Big Board Development Kit in collaboration with the python requests package to retrieve and display relevant US Covid-19 information on a TFT screen. It was created as the final project for MIT's 6.115 Microcomputer Project Laboratory class taught by the amazing Professor Steven Leeb.

To run:
	Navigate to BunkerKnowledge/SerialConnections and run:
	'python start_bunker_knowledge.py'

Folder Breakdown:
	Covid19Data       - Storage spot for the Covid-19 dataset retrieved by the system.
					      becomes stale in 1 hour.
	PSoC5_Files       - Stores all PSoC Creator files used to program the PSoC 5. Uses the emWin package,
					      which users will need to install prior to use.
	RetrievalSystem   - Uses python requests package to retrieve and store up to date Covid-19 
					      information using API calls to two different sources.
	SerialConnections - Entry point to the code, runs a terminal style interface where commands can be input
						  and displayed on the TFT Screen.