// Copyright Epic Games, Inc. All Rights Reserved.

#include "OpenWorldEditorPlugin.h"
#include "Modules/ModuleInterface.h"
#include "Modules/ModuleManager.h"
#include "AssetTypeActions/AssetTypeActions_OWPathAsset.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleRegistry.h"
#include "EditorModeRegistry.h"
#include "Editors/PathAssetEdMode/OWPathAssetEdMode.h"
#include "OpenWorldEditorPluginStyle.h"

#define LOCTEXT_NAMESPACE "FOpenWorldEditorPluginModule"

void FOpenWorldEditorPluginModule::StartupModule()
{
	FOpenWorldEditorPluginStyle::Get();

	FEditorModeRegistry::Get().RegisterMode<FOWPathAssetEdMode>(FOWPathAssetEdMode::EM_OWPathAssetEdModeId, LOCTEXT("PedPathEdModeName", "Open World Path Editor"), FSlateIcon(FOpenWorldEditorPluginStyle::Get().GetStyleSetName(), "OWPathAssetEdMode", "OWPathAssetEdMode.small"), true);

	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	OpenWorldAssetCategoryBit = AssetTools.RegisterAdvancedAssetCategory(FName(TEXT("OpenWorld")), LOCTEXT("OpenWorldAssetCategory", "Open World"));

	RegisterAssetTypeAction(AssetTools, MakeShareable(new FAssetTypeActions_OWPathAsset(OpenWorldAssetCategoryBit)));
}

void FOpenWorldEditorPluginModule::ShutdownModule()
{
	FEditorModeRegistry::Get().UnregisterMode(FOWPathAssetEdMode::EM_OWPathAssetEdModeId);
	UnRegisterAssetTypeAction();
}

void FOpenWorldEditorPluginModule::UnRegisterAssetTypeAction()
{
	FAssetToolsModule* AssetToolsModule = FModuleManager::GetModulePtr<FAssetToolsModule>("AssetTools");
	if (AssetToolsModule != nullptr) {
		IAssetTools& AssetTools = AssetToolsModule->Get();

		for (auto Action : RegisteredAssetTypeActions) {
			AssetTools.UnregisterAssetTypeActions(Action.ToSharedRef());
		}
	}
}

void FOpenWorldEditorPluginModule::RegisterAssetTypeAction(IAssetTools& AssetTools, TSharedRef<IAssetTypeActions> Action)
{
	AssetTools.RegisterAssetTypeActions(Action);
	RegisteredAssetTypeActions.Add(Action);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FOpenWorldEditorPluginModule, OpenWorldEditorPlugin)