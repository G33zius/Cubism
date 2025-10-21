<!-- Copilot instructions for AI coding agents working on the Cubism UE5 project -->
# Cubism — Quick agent guide

This file gives focused, actionable guidance for AI coding agents (including Copilot) to be immediately productive in this Unreal Engine 5 project.

Operate at the repository root: all commands and relative paths assume the workspace root contains `Cubism.uproject`.

1. Big picture
- This is an Unreal Engine 5 (UE5) C++ project that lives in the `Source/Cubism` module. The game code is in `Source/Cubism` and primary targets are `Cubism` and `CubismEditor` (see `Source/*.Target.cs`).
- The engine (UE_5.6) is present alongside the project at `d:\Program Files\Epic Games\UE_5.6`. Editor and build tools are expected to come from that engine install.

2. Build / run workflows
- Typical build (Windows): use the provided UE build scripts from the engine. From the workspace root run the Engine Build Batch files, e.g.:
  - Build the editor or project using: `Engine\\Build\\BatchFiles\\Build.bat CubismEditor Win64 Development <path-to>.uproject -waitmutex` (the workspace tasks included in this repo already call this exact command).
- If editing C++ files, regenerate project files by right-clicking the `.uproject` in the Editor or run `GenerateProjectFiles.bat` from the engine/UE folder.
- Use Visual Studio 2022 for debugging and compilation (Project Setup recommends VS2022). The project uses typical UE5 build settings — prefer IDE build for iterative C++ work.

3. Project-specific conventions
- Code lives under `Source/Cubism` and follows UE naming and filestructure conventions: actor classes derive from AActor and live in files like `Cube.h`/`Cube.cpp`.
- Traces and gameplay logic frequently use named collision profiles such as `CubieTrace` (see `Source/Cubism/Cube.cpp`). If changing traces, search for `LineTrace*` and adjust collision profiles in `Project Settings` or `DefaultEngine.ini`.
- Primary game actors often expose booleans like `IsCenterCubie`, `IsExitCubie`, `IsEntranceCubie`, etc. Keep checks for these flags when selecting or filtering actors (example: `FindNextShiftCubie` in `Cube.cpp`).

4. Important files to reference
- `Source/Cubism/Cube.cpp` — example of line tracing, actor filtering, and coordinate <-> location conversions.
- `Source/Cubism/*.Target.cs` — build targets for editor and game.
- `Cubism.uproject` — project descriptor; contains plugin/module references and should be used as the primary entry point for Editor commands.
- `Project Setup.md` — local developer setup links (UE5, VS2022, Git LFS). Use it to understand expected developer environment.

5. Tests & tools
- There are no repository-level unit tests discovered. The engine contains many internal tests; for quick validation, compile the project and run the editor.

6. Common pitfalls & patterns
- Don't change engine files under `d:\Program Files\Epic Games\\UE_5.6` unless providing a patch that you intend to propagate; prefer modifying project source under `Source/`.
- Use existing named collision profiles rather than hardcoding channel numbers.
- Many runtime arrays are filtered using UE container utilities (`Algo::RandomShuffle`, `TArray::AddUnique`, `Cast<>`), so preserve container semantics and `IsValid` checks.

7. Examples (quick edits)
- To add a debug trace path for ShiftCubie selection, update `LineTraceForShiftCubie` in `Source/Cubism/Cube.cpp` and reuse the `CubieTrace` profile.
- To adjust cubie indexing, inspect `GetIndicesSetCubieCount` and update `Dimensions` handling in the actor's header.

8. When to ask the developer
- If a proposed change affects Editor project settings (`Default*.ini`) or `.uproject` plugins, confirm before editing.
- If a code change requires rebuilding the engine or editing engine source, ask for permission and provide a minimal patch and build plan.

9. Merge guidance
- If this file already exists, preserve any custom workflow snippets (e.g., CI build steps) and append missing project-specific entries above.

10. Contact / verification
- After making changes, run a local build (IDE or `Build.bat`) and if possible launch the editor to verify no obvious runtime crashes.

References: `Project Setup.md`, `README.md`, `Source/Cubism/Cube.cpp`, `Cubism.uproject`.

If any section above is incomplete or you want additional examples (packaged build steps, common Editor settings, or code-style rules), tell me which area to expand.
