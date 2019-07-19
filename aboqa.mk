##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=aboqa
ConfigurationName      :=Debug
WorkspacePath          :=/home/wahid/Storage/GitHub/aboqa
ProjectPath            :=/home/wahid/Storage/GitHub/aboqa
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Wahid
Date                   :=19/07/19
CodeLitePath           :=/home/wahid/.codelite
LinkerName             :=/usr/bin/g++
SharedObjectLinkerName :=/usr/bin/g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="aboqa.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch)/usr/local/include $(IncludeSwitch)/opt/ncurses/include/ncursesw $(IncludeSwitch)/opt/ncurses/include $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)TUCUT $(LibrarySwitch)boost_filesystem $(LibrarySwitch)ncursesw 
ArLibs                 :=  "TUCUT" "boost_filesystem" "ncursesw" 
LibPath                := $(LibraryPathSwitch). $(LibraryPathSwitch)/usr/local/lib $(LibraryPathSwitch)/opt/ncurses/lib $(LibraryPathSwitch)./submodules/TUCUT/Debug 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := /usr/bin/ar rcu
CXX      := /usr/bin/g++
CC       := /usr/bin/gcc
CXXFLAGS := -g -std=c++17 -Wall -Wextra -g -O0 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/aboqa_SplashWindow.cpp$(ObjectSuffix) $(IntermediateDirectory)/aboqa_CharacterSystem.cpp$(ObjectSuffix) $(IntermediateDirectory)/aboqa_MainWindow.cpp$(ObjectSuffix) $(IntermediateDirectory)/aboqa_InventoryWindow.cpp$(ObjectSuffix) $(IntermediateDirectory)/aboqa_ExitWindow.cpp$(ObjectSuffix) $(IntermediateDirectory)/aboqa_main.cpp$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d ".build-debug/s-TUCUT" $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

".build-debug/s-TUCUT":
	@$(MakeDirCommand) ".build-debug"
	@echo stam > ".build-debug/s-TUCUT"




MakeIntermediateDirs:
	@test -d ./Debug || $(MakeDirCommand) ./Debug


$(IntermediateDirectory)/.d:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/aboqa_SplashWindow.cpp$(ObjectSuffix): aboqa/SplashWindow.cpp $(IntermediateDirectory)/aboqa_SplashWindow.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/wahid/Storage/GitHub/aboqa/aboqa/SplashWindow.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/aboqa_SplashWindow.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/aboqa_SplashWindow.cpp$(DependSuffix): aboqa/SplashWindow.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/aboqa_SplashWindow.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/aboqa_SplashWindow.cpp$(DependSuffix) -MM aboqa/SplashWindow.cpp

$(IntermediateDirectory)/aboqa_SplashWindow.cpp$(PreprocessSuffix): aboqa/SplashWindow.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/aboqa_SplashWindow.cpp$(PreprocessSuffix) aboqa/SplashWindow.cpp

$(IntermediateDirectory)/aboqa_CharacterSystem.cpp$(ObjectSuffix): aboqa/CharacterSystem.cpp $(IntermediateDirectory)/aboqa_CharacterSystem.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/wahid/Storage/GitHub/aboqa/aboqa/CharacterSystem.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/aboqa_CharacterSystem.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/aboqa_CharacterSystem.cpp$(DependSuffix): aboqa/CharacterSystem.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/aboqa_CharacterSystem.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/aboqa_CharacterSystem.cpp$(DependSuffix) -MM aboqa/CharacterSystem.cpp

$(IntermediateDirectory)/aboqa_CharacterSystem.cpp$(PreprocessSuffix): aboqa/CharacterSystem.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/aboqa_CharacterSystem.cpp$(PreprocessSuffix) aboqa/CharacterSystem.cpp

$(IntermediateDirectory)/aboqa_MainWindow.cpp$(ObjectSuffix): aboqa/MainWindow.cpp $(IntermediateDirectory)/aboqa_MainWindow.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/wahid/Storage/GitHub/aboqa/aboqa/MainWindow.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/aboqa_MainWindow.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/aboqa_MainWindow.cpp$(DependSuffix): aboqa/MainWindow.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/aboqa_MainWindow.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/aboqa_MainWindow.cpp$(DependSuffix) -MM aboqa/MainWindow.cpp

$(IntermediateDirectory)/aboqa_MainWindow.cpp$(PreprocessSuffix): aboqa/MainWindow.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/aboqa_MainWindow.cpp$(PreprocessSuffix) aboqa/MainWindow.cpp

$(IntermediateDirectory)/aboqa_InventoryWindow.cpp$(ObjectSuffix): aboqa/InventoryWindow.cpp $(IntermediateDirectory)/aboqa_InventoryWindow.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/wahid/Storage/GitHub/aboqa/aboqa/InventoryWindow.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/aboqa_InventoryWindow.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/aboqa_InventoryWindow.cpp$(DependSuffix): aboqa/InventoryWindow.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/aboqa_InventoryWindow.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/aboqa_InventoryWindow.cpp$(DependSuffix) -MM aboqa/InventoryWindow.cpp

$(IntermediateDirectory)/aboqa_InventoryWindow.cpp$(PreprocessSuffix): aboqa/InventoryWindow.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/aboqa_InventoryWindow.cpp$(PreprocessSuffix) aboqa/InventoryWindow.cpp

$(IntermediateDirectory)/aboqa_ExitWindow.cpp$(ObjectSuffix): aboqa/ExitWindow.cpp $(IntermediateDirectory)/aboqa_ExitWindow.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/wahid/Storage/GitHub/aboqa/aboqa/ExitWindow.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/aboqa_ExitWindow.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/aboqa_ExitWindow.cpp$(DependSuffix): aboqa/ExitWindow.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/aboqa_ExitWindow.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/aboqa_ExitWindow.cpp$(DependSuffix) -MM aboqa/ExitWindow.cpp

$(IntermediateDirectory)/aboqa_ExitWindow.cpp$(PreprocessSuffix): aboqa/ExitWindow.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/aboqa_ExitWindow.cpp$(PreprocessSuffix) aboqa/ExitWindow.cpp

$(IntermediateDirectory)/aboqa_main.cpp$(ObjectSuffix): aboqa/main.cpp $(IntermediateDirectory)/aboqa_main.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/wahid/Storage/GitHub/aboqa/aboqa/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/aboqa_main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/aboqa_main.cpp$(DependSuffix): aboqa/main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/aboqa_main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/aboqa_main.cpp$(DependSuffix) -MM aboqa/main.cpp

$(IntermediateDirectory)/aboqa_main.cpp$(PreprocessSuffix): aboqa/main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/aboqa_main.cpp$(PreprocessSuffix) aboqa/main.cpp


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


