{
    "version": "2.0.0",
    "tasks": [
        {
            "label": "build",
            "type": "shell",
            "command": "g++",
            "args": [
                "-std=c++11",
                "-Wall",
                "-Wextra",
                "-O2",
                "-o",
                "sphere_points",
                "main.cpp",
                "point3d.cpp", 
                "spheregenerator.cpp",
                "filemanager.cpp",
                "menu.cpp"
            ],
            "group": {
                "kind": "build",
                "isDefault": true
            },
            "problemMatcher": ["$gcc"]
        },
        {
            "label": "clean",
            "type": "shell",
            "command": "rm",
            "args": ["-f", "sphere_points", "points.txt"],
            "group": "build"
        },
        {
            "label": "run",
            "type": "shell", 
            "command": "./sphere_points",
            "group": "test",
            "dependsOn": "build"
        }
    ]
}
