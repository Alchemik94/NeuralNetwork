<?xml version="1.0"?><doc>
<members>
<member name="T:Program" decl="false" source="c:\users\grzegorz\dropbox\github\neuralnetwork\neuralnetwork\main.cpp" line="10">
<summary>
Simple class containing whole program work. Made to make sure that every variable can be used in functions.
</summary>
</member>
<member name="M:Program.TeachingFront(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="false" source="c:\users\grzegorz\dropbox\github\neuralnetwork\neuralnetwork\main.cpp" line="31">
<summary>
Teaches the front part of selected neural network. Reads everything from file, parses and then teaches the network.
</summary>
<param name="teachingFileName">Name of file containing teaching set as proteins and their secondary structure.</param>
</member>
<member name="M:Program.TeachingMiddle(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="false" source="c:\users\grzegorz\dropbox\github\neuralnetwork\neuralnetwork\main.cpp" line="42">
<summary>
Teaches the middle part of selected neural network. Reads everything from file, parses and then teaches the network.
</summary>
<param name="teachingFileName">Name of file containing teaching set as proteins and their secondary structure.</param>
</member>
<member name="M:Program.TeachingBack(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="false" source="c:\users\grzegorz\dropbox\github\neuralnetwork\neuralnetwork\main.cpp" line="53">
<summary>
Teaches the ending part of selected neural network. Reads everything from file, parses and then teaches the network.
</summary>
<param name="teachingFileName">Name of file containing teaching set as proteins and their secondary structure.</param>
</member>
<member name="M:Program.Help" decl="false" source="c:\users\grzegorz\dropbox\github\neuralnetwork\neuralnetwork\main.cpp" line="65">
<summary>
Prints out options to use by user.
</summary>
</member>
<member name="M:Program.GetStructure" decl="false" source="c:\users\grzegorz\dropbox\github\neuralnetwork\neuralnetwork\main.cpp" line="83">
<summary>
Asks user to insert a structure of neural network.
</summary>
<returns>Vector used to create new neural vector</returns>
</member>
<member name="M:Program.GetName" decl="false" source="c:\users\grzegorz\dropbox\github\neuralnetwork\neuralnetwork\main.cpp" line="110">
<summary>
Asks user to give the name for new neural network
</summary>
<returns>Name of new network</returns>
</member>
<member name="M:Program.Teach" decl="false" source="c:\users\grzegorz\dropbox\github\neuralnetwork\neuralnetwork\main.cpp" line="123">
<summary>
Teaches every part of user-side network.
</summary>
</member>
<member name="M:Program.GetFilename" decl="false" source="c:\users\grzegorz\dropbox\github\neuralnetwork\neuralnetwork\main.cpp" line="140">
<summary>
Asks user to give the name of network directory.
</summary>
<returns>Network directory name</returns>
</member>
<member name="M:Program.RunOnCase" decl="false" source="c:\users\grzegorz\dropbox\github\neuralnetwork\neuralnetwork\main.cpp" line="153">
<summary>
Uses selected neural network to work on a single case. Asks user for case filename, parses it, predicts secondary structure and saves it.
</summary>
</member>
<member name="M:Program.Run" decl="false" source="c:\users\grzegorz\dropbox\github\neuralnetwork\neuralnetwork\main.cpp" line="189">
<summary>
Runs the program.
</summary>
</member>
</members>
</doc>