# UI Host (Server) – Project Overview



This document describes the UI host (server) part of the project. Per the frozen configuration, it is implemented as an independent application hosted on an SBC (single board computer) according to system requirements.



 ## Architecture Overview



The server consists of four main components:



 -  * *Web App * * – Allows setting working parameters and viewing device status.  

 -  * *RPC Engine * * – Verifies UI requests and dispatches them to lower layers.  

 -  * *Animation Manager * * – Handles animation sequences, builds packets, and communicates with the device.  

 -  * *Communication Layer * * – Manages the physical link to the device and ensures reliable data transmission.  



>  * *Note: * * All LEDs are assumed to emit the same color simultaneously.



 ## Requirements



 -  * *COM _1–3: * * Communication layer handles link status, uses UART, and a unified protocol.  

 -  * *CFG _1: * * IP must be configured before app initialization.  

 -  * *UI _1–3: * * UI shows status, allows changing parameters, and creating animations.  

 -  * *RPC _1: * * RPC verifies requests from UI and passes them to the Animation Manager.  

 -  * *ANIM _1–2: * * Animation Manager periodically updates strip status; default is strip off.



