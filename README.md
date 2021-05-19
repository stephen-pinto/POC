
# All proof-of-concept projects

### It contains below projects merged into a single repository:


 1.  **PointyBoot** : 
  _A C# version of SpringBoot Depenedency management framework._
      
      - This is just a DI framework to solve DI for functions, properties and classes like how SpringBoot works. Needs more performance improvement.
      - The name derives from C#'s Sharp and SpringBoot's Boot = SharpBoot = PointyBoot :stuck_out_tongue_winking_eye:
      - Works with the primary use-case. Also contains performance tests in TestApp project.
      - **Based on:**  Plain C# with Reflection.
      - You can find the code for this whole project here: [PointyBoot](https://github.com/stephen-pinto/POC/tree/main/PointyBoot)

5.  **ComCSharpInteropLibraries** : 
  _This solution is supposed to hold all interop libraries. At present it contains a ADO like client for Firebird DB based on COM (OLE)_
  
      - The goal of this project was to create a custom ADO like client for firebird getting all information about its DDF and other information and provide connection to .NET clients.
      - The idea is to use COM for its architecture.
      - It works when getting information about existing tables and running query.
      - **Based on:** VC++, ComponentObjectModel (OLE).
      - You can find its code here: [ComCSharpIteropLibraries](https://github.com/stephen-pinto/POC/tree/main/ComCSharpIteropLibraries)
      
