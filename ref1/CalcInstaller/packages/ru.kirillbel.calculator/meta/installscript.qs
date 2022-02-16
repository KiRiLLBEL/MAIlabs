function Component()
{
    // default constructor
}

Component.prototype.createOperations = function()
{
    // This actually installs the files
    component.createOperations();

    if (systemInfo.productType == "windows") {
        // Start menu shortcut
        component.addOperation("CreateShortcut", 
                               "@TargetDir@/CalcMulti.exe", 
                               "@StartMenuDir@/Calculator.lnk", 
                               "workingDirectory=@TargetDir@", 
                               "iconPath=@TargetDir@/Icon/IconCalc.ico");

       // Desktop Shortcut
       component.addOperation("CreateShortcut", 
                              "@TargetDir@/CalcMulti.exe",
                              "@DesktopDir@/Calculator @Version@.lnk",
                              "workingDirectory=@TargetDir@", 
                              "iconPath=@TargetDir@//Icon/IconCalc.ico");
    }
}