#include <iostream>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <cstring>
#include <unistd.h>

int main( int p_Argc, char **p_ppArgv )
{
	std::cout << "Testing server" << std::endl;

	int Socket;
	struct addrinfo Hints, *pServerInfo, *pServerItr;
	
	memset( &Hints, 0, sizeof( Hints ) );
	Hints.ai_family = AF_UNSPEC;
	Hints.ai_socktype = SOCK_DGRAM;

	if( getaddrinfo( "127.0.0.1", "5096", &Hints, &pServerInfo ) != 0 )
	{
		std::cout << "Could not get address information" << std::endl;
		return 1;
	}

	for( pServerItr = pServerInfo; pServerItr != NULL; pServerInfo = pServerInfo->ai_next )
	{
		if( ( Socket = socket( pServerItr->ai_family, pServerItr->ai_socktype,
			pServerItr->ai_protocol ) ) == -1 )
		{
			std::cout << "Couldn't get the socket" << std::endl;
			continue;
		}

		break;
	}

	if( pServerItr == NULL )
	{
		std::cout << "Failed to create socket" << std::endl;
		return 1;
	}

	sendto( Socket, "Hello", strlen( "Hello" ), 0, pServerItr->ai_addr,
		pServerItr->ai_addrlen );

	freeaddrinfo( pServerInfo );

	close( Socket );

	return 0;
}

