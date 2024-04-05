# DNS proxy server
## Write DNS proxy server with a domains blacklist feature to filter unwanted host names resolving.

### Functional requirements:

- The proxy server reads its parameters during startup from the configuration file.

- The configuration file contains the following parameters:
        
        IP address of upstream DNS server
        
        List of domain names to filter resolving ("blacklist")
        
        Type of DNS proxy server's response for blacklisted domains (not found,      
        refused, resolve to a pre-configured IP address)

- DNS proxy server uses UDP protocol for processing client's requests and for interaction with upstream DNS server.

- If a domain name from a client's request is not found in the blacklist, then the proxy server forwards the request to the upstream DNS server, waits for a response, and sends it back to the client.

- If a domain name from a client's request is found in the blacklist, then the proxy server responds with a response defined in the configuration file.


### Non-functional requirements:

- Programming language: C

- It is allowed to use third-party libraries or code. If you use one then you must   
comply with its license terms and conditions.

- All other requirements and restrictions are up to your discretion.

### Expectations:

#### What we expect to receive from you when you complete this task:

- Source code of DNS proxy server written according to the requirements. Source code 
    should be in a plain ASCII text (it is not a joke - sometimes we receive source code in MS Word document).

- Instruction how to build, configure and run the proxy server (including necessary files like Makefile etc).

- Description how you tested the proxy server.

- Document, if your solution has additional (known to you) limitations or restrictions, or it has more features that it was requested.

- If you have GitHub (or similar) account then you can publish everything there; otherwise, put everything into an archive.