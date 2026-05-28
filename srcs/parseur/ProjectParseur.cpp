#include "ProjectParseur.hpp"

static Project	&ProjectParseur::start(const std::string &path)
{
	std::ifstream file(path);

	json data;
	file >> data;

	for (auto &p : data["projects"])
	{
		Project project;

		project.title = p["title"];
		project.description = p["description"];
		project.imagePath = p["imagePath"];
		project.githubUrl = p["githubUrl"];

		for (auto &tag : p["tags"])
			project.tags.push_back(tag);

		projects.push_back(project);
	}
}