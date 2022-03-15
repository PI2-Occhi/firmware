OCCHI_PATH_IMAGE:=/etc/occhi/source.png

export OCCHI_PATH_IMAGE

clean:
	@find ./ -name '__pycache__' -exec rm -rf {} \;
	@rm -rf .cache
	@rm -rf .pytest_cache
	@rm -rf build
	@rm -rf dist
	@rm -rf *.egg-info

envs: 
	@echo $(OCCHI_PATH_IMAGE)

takephoto:
	python camocchi/test.py

check:
	black camocchi/*.py
	black tests/unit/*.py
	flake8 camocchi/*.py
	flake8 tests/unit/*.py
	mypy tests
	mypy camocchi

flake:
	flake8 camocchi/*.py
	flake8 tests/unit/*.py

black:
	black camocchi/*.py
	black tests/unit/*.py

test:
	pytest
